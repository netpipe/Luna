"""Tests for our main skele CLI module."""


from subprocess import PIPE, Popen as popen
from unittest import TestCase

from klear import __version__ as VERSION


class TestHelp(TestCase):
    def test_returns_usage_information(self):
        output = popen(["klear", "--help"], stdout=PIPE).communicate()[0]
        self.assertTrue("Usage:" in str(output))
