Run with:
```
./build.sh && stdbuf -i 0 -e 0 -o 0 ./pipe
```

and then
```
node rt_pipe_node.js
```

Notes:
* after a while the pipe will be full because Xenomai is writing faster than node reads. Killing node flushes the queue (apparently)
* `fs.read()` is blocking: it will return only when data is available from the pipe
* `readTask` and `writeTask` always stay in primary mode
