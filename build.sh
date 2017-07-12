#!/bin/bash
git checkout release && \
git merge master && \
#cmake . && make \
#i686-w64-mingw32.static-qmake-qt5 && make \
git add . && \
git commit -m "release" && \
git push -f origin release && \
git checkout master 
