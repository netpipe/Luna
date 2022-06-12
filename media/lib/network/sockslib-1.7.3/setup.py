import pathlib
from setuptools import setup

# The directory containing this file
HERE = pathlib.Path(__file__).parent

# The text of the README file
README = (HERE / "README.md").read_text()

# This call to setup() does all the work
setup(
    name="sockslib",
    version="1.7.3",
    description="Simple Socks proxy library",
    long_description=README,
    long_description_content_type="text/markdown",
    url="https://github.com/woo200/sockslib",
    author="Jack Woo",
    author_email="woo.jack.06@gmail.com",
    license="MIT",
    classifiers=[
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.9",
    ],
    packages=["sockslib"],
    include_package_data=True,
    install_requires=[],
    entry_points={},
)
