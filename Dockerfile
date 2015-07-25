FROM alpine:3.1
MAINTAINER Pablo Opazo <pablo@sequel.ninja>
RUN apk add --update gcc git
RUN git clone git@github.com:p404/http_server.git /home/webserver
RUN cd /home/webserver && gcc webserver.c -o server
EXPOSE 80
CMD ["./home/webserver/server"]
ENTRYPOINT  /bin/sh
