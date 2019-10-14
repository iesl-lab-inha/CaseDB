# CaseDB

We have implemented this on top LevelDB to understands the performance improvements. 

It extends CLeveldb and improves persistent storage structure to improve write performance
Main idea is to seperate key-offset pairs to values and bloom filters in different metadata files and implement LSM-tree archhitecture on that

## Contribution:

We have created a program called casedb_test.cc which uses LevelDB architecture to save Key and Value Offset

