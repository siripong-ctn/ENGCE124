#!/bin/bash
read -p "Commit input: " commit
git add .
git commit -m "$commit"
echo "Commit success!"