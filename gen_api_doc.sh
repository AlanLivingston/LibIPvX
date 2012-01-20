#!/bin/bash

# Copyright (C) 2012  The FOSS Project
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# This script uses ROBODoc to generate LIBIPvX's API documentation.
# Simple run it without arguements e.g. ./doc_gen

DOC_DIR=doc
SRC_DIR=.
ROBODOC_BIN=/usr/bin/robodoc

echo "Generating LIBIPvX API documentation..";

${ROBODOC_BIN} --src ${SRC_DIR} --doc ${DOC_DIR} --multidoc --html --index --tell

echo "Finished!";

