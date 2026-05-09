FROM node:22.22.2-alpine3.23
WORKDIR /usr/share/kreuzstich

COPY dist/LICENSE /usr/share/kreuzstich
COPY dist/VERSION /usr/share/kreuzstich
COPY dist/data-web/* /usr/share/kreuzstich

RUN npm ci --omit dev

CMD ["node", "index.cjs"]
