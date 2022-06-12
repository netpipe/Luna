import time
import queue

from dataclasses import dataclass, field
from typing import Dict, Callable, Any, List

from .exceptions import HandlerMissingException


class EventHandler():
    """Super class that registers and handle events, for objects such as Peer and Connection."""

    def __init__(self, event_names: List[str], handlers: Dict[str, Callable[[Any], Any]], min_handler_names: List[str] = None):
        if min_handler_names is None:
            min_handler_names = []

        self.event_names = event_names
        self.handlers = handlers
        self.min_handler_names = min_handler_names

        self.event_queues = {event_name: queue.Queue(maxsize=1) for event_name in event_names}
        self.waiting_threads = {event_name: 0 for event_name in event_names}

    def _register(self, event_name: str, *args):
        """Registers an event with specific arguments, so that consumer threads can handle it.

        Args:
            event_name (str): the event to trigger.

        Raises:
            ValueError: if event_name is not a valid event name for this handler.
        """
        if event_name not in self.event_names:
            raise ValueError(f"{event_name} is not a valid event name for {self.__name__}!")

        self.event_queues[event_name].put(args)  # will block until a slot is available

    def handle(self, event_name: str, *args) -> Any:
        """Calls a handler for a specific event if existing, passing it arguments.

        Args:
            event_name (str): the event to trigger.

        Returns:
            Any: whatever the handler, if existing, returns 
        """
        self._register(event_name, *args)

        if self.waiting_threads[event_name] > 0:
            time.sleep(1e-12)  # pass the handle to the waiting thread

        return self.wait(event_name, timeout=0)

    def set_handler(self, handler_type: str, handler: Callable):
        """Sets a callable as an event handler.

        Args:
            handler_type (str): the event name.
            handler (Callable): the handler to be called when event is triggered.
        """
        self.handlers[handler_type] = handler

    def wait(self, event_name: str, timeout: float = None) -> Any:
        """Waits for an event to trigger and returns the handler's return value.

        Args:
            event_name (str): the event to wait for.
            timeout (float, optional): how long maximum to wait for the event, in seconds. Defaults to None.

        Raises:
            ValueError: if event_name is not a valid event name for this handler.
            HandlerMissingException: if no handler is registered for the event, while it is a necessary handler.

        Returns:
            Any: whatever the handler returns.
        """
        if event_name not in self.event_names:
            raise ValueError(f"{event_name} is not a valid event name for {self.__name__}!")

        self.waiting_threads[event_name] += 1  # notify other threads that we are listening for this event

        block = timeout is None or timeout > 0
        try:
            args = self.event_queues[event_name].get(block=block, timeout=timeout)
        except queue.Empty:
            return  # no item in the queue within the timeout window
        finally:
            self.waiting_threads[event_name] -= 1  # we are no longer listening for this event

        handler = self.handlers.get(event_name, None)
        if handler is not None:
            return handler(self, *args)
        elif event_name in self.min_handler_names:
            raise HandlerMissingException(f"{self.__name__} must have the following handlers: {self.min_handler_names}")
