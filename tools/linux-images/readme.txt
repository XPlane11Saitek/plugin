Build images
```
docker build -t tarasmal/saitek:<os> -f tools/linux-images/<os> ./
```
Compile
```
docker  run  -v `pwd`:/app -w /app -t tarasmal/saitek:cmake 
```