FROM ubuntu:14.04
MAINTAINER Pablo Opazo <pablo@sequel.ninja>
RUN apt-get update
RUN apt-get -y install git gcc-4.6-base cpp-4.6 libgomp1 libquadmath0 libc6-dev
RUN git clone https://github.com/p404/http_server /home/webserver
RUN cd /home/webserver && gcc webserver.c -o server
EXPOSE 80
CMD ["./home/webserver/server"]
