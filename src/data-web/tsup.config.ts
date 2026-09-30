/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { defineConfig } from 'tsup';
import type { Plugin } from 'esbuild';
import loadSqlFile from './sqlPlugin';

const sqlPlugin: Plugin = {
    name: 'sql-loader',
    setup(build) {
        build.onLoad({ filter: /\.sql$/ }, async (args) => {
            return {
                contents: await loadSqlFile(args.path, args.with),
                loader: 'js'
            };
        });
    },
};

export default defineConfig({
    entry: ['src/index.ts'],
    esbuildPlugins: [sqlPlugin],
});
