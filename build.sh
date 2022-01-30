#!/bin/bash

set -ex

make
./coni $1 $2 $3 $4
