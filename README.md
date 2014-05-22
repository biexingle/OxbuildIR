Instance Retrieval (Oxford Building)
====================================

Sample Usage
------------

```bash
$ cd src; make 
# create inverted index
$ ./buildIndex -d ../oxford_building_dataset/word_oxc1_hesaff_sift_16M_1M/ -o invIndex2.txt -c invIndexFreq2.txt -s imgStats.txt
$ bash runIR.sh -q oxc1_all_souls_000013
```

Batch Usage
...........

Use `-o` and `-f` to give input from file

Eg in :
```bash
$ bash runIR_batch <inp file with list of images> <output dir>
```

Evalutaion
----------

1. Copy the `config.sh.sample` to `config.sh` and set the parameter values
```bash
$ bash compute_map.sh ~/work/project/datasets/oxford_building/gt/ ../oxford_building_dataset/compute_ap 
```
