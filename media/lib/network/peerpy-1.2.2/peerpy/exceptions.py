class HandlerMissingException(Exception):
    """Raised when an event handler is missing a handler for a specific event."""
    pass


class DataTypeError(Exception):
    """Raised when data type doesn't correspond to the connection's data type."""
    pass


class HeaderSizeError(Exception):
    """Raised when the header's size is greater than the protocol's header size."""
    pass


class DataSizeError(Exception):
    """Raised the data size doesn't correspond to the connection's data size."""
    pass
