#!/bin/bash
read -p msg
git add * && git commit -m '$msg' && git push