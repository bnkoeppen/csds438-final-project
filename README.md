# csds438 project

## How to run in Markov:
1. Clone the repository
2. Open a local command window and run the following command:
```
scp -r ${local path to git repository} ${your case id}@markov.case.edu:
```
an example of this is:
```
scp -r "D:\Github (local)\csds438-project" jdr161@markov.case.edu:
```
3. Navigate into the "csds438 project" directory in Markov
4. Submit the slurm script: ```sbatch runTestsJob.slurm```
