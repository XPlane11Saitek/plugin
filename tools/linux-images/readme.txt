Build images
```
docker build -t tarasmal/saitek:cmake -f tools/linux-images/Dockerfile ./
```
Compile
```
docker  run  -v `pwd`:/app -w /app -t tarasmal/saitek:cmake 
```