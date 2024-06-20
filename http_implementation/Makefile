
output: http_client.o 
	gcc http_client.o -o output

http_client.o: http_client.c
	gcc -c http_client.c 

remove:
	rm *.o http_server http_client output
	ls | grep -v "\." | xargs rm
# ls lists all files, passes those files to grep -v ".\" means select all files wihtout a ".", and pass those to xargs rm, which removes them