FROM nginx:1.29.3
RUN rm /usr/share/nginx/html/*
COPY dist/docker/kreuzstich/nginx.conf /etc/nginx/nginx.conf
COPY dist/LICENSE /usr/share/nginx/html/
COPY dist/VERSION /usr/share/nginx/html/
COPY dist/gui-web/*  /usr/share/nginx/html/
