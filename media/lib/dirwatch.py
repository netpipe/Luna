import os
import os.path
import time


class DirWatcher(object):
    """Watches for changes in specified file or directory"""
    def __init__(self, file_or_directory):
        self.file_or_directory = file_or_directory
        self._state = self._build_state()

    def watch(self, sleep=1):
        """
        Watches for changes in specified file and yields tuples (added_files,
        changed_files, removed_files)
        """
        while True:
            try:
                time.sleep(sleep)
                added, changed, removed = self.recheck()
                if any(added or changed or removed):
                    yield added, changed, removed
            except Exception:
                raise

    def recheck(self):
        new_state = self._build_state()

        new_keys = set(new_state.keys())
        old_keys = set(self._state.keys())

        added = new_keys - old_keys
        removed = old_keys - new_keys
        changed = {x for x in old_keys.intersection(new_keys)
                   if new_state[x] != self._state[x]}

        self._state = new_state

        return added, changed, removed

    def _build_state(self):
        result = {}
        for fn in self._iter_files():
            try:
                result[fn] = os.path.getmtime(fn)
            except OSError:
                pass
        return result

    def _iter_files(self):
        if os.path.isfile(self.file_or_directory):
            yield os.path.abspath(self.file_or_directory)
        elif os.path.isdir(self.file_or_directory):
            for path, dirnames, filenames in os.walk(self.file_or_directory):
                for fn in filenames:
                    yield os.path.abspath(os.path.join(path, fn))


def watchdir(file_or_directory, interval=1):
    """
    Watches for changes in directory and yields names of changed files, added
    files and removed files as tuples (added, changed, removed)
    """
    return DirWatcher(file_or_directory).watch(interval)


if __name__ == '__main__':
    for added, changed, removed in watchdir('/tmp/'):
        print 'Added: %s' % added
        print 'Changed: %s' % changed
        print 'Removed: %s' % removed
        print ''
