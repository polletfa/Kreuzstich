FROM node:26.10.0-alpine3.23
WORKDIR /usr/share/kreuzstich

COPY dist/LICENSE /usr/share/kreuzstich
COPY dist/VERSION /usr/share/kreuzstich
COPY dist/data-web/* /usr/share/kreuzstich

RUN npm ci --omit dev

CMD ["node", "index.cjs"]
