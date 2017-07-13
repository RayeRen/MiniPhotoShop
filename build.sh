#!/bin/bash
#cmake . && make \
#i686-w64-mingw32.static-qmake-qt5 && make \
git checkout release && \
git merge master && \
git add . && \
git commit -m "release" && \
git push -f origin release \