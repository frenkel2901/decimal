# decimal

school project decimal


to build Docker 

run run.sh

or

docker build -t my_c_project -f test_build/Dockerfile .
docker run -p 8000:8000 -it my_c_project

or

docker rmi -f my_c_project
docker build -t my_c_project -f test_build/Dockerfile .
docker run -p 8000:8000 --rm -it my_c_project

for mac can try docker run -v /var/run/docker.sock:/var/run/docker.sock -p 8000:8000 -it my_c_project


open ur browser and go to
http://localhost:8000

! dont make ctrl + c in ur console b4 u stop testing


valgrind in Docker

copy leaks with valgrind from container to local 
docker cp NAME:/usr/src/app/valgrind_test.txt ./

to check container NAME
docker ps

to connect container
docker exec -t -i NAME /bin/bash
can make "ls" to check what is inside container
to exit
exit


how to use run_tests.sh and tests/process_tests.py

scripts can be used to move failed tests from *.check files to error.check file, so you can make gcov_report to see coverage

1) go to src and run ./run_tests.sh
if need rules first do
chmod +x run_tests.sh

it will create failed_f.txt
move failed_f.txt to your tests directory or leave in src, if ypur tests are in src

2) go to dir with tests and run python3 process_tests.py or python process_tests.py

it will create error.check and remove shitty tests from check files
