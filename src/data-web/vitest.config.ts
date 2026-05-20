/*
  Kreuzstich
  Copyright (c) 2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { defineConfig } from 'vitest/config'
import fs from 'fs/promises';
import path from 'path';
import loadSqlFile from './sqlPlugin';

const vitestSqlPlugin = {
    name: 'vitest-sql-loader-with-attributes',

    // extract import attributes and add to resolved path (in the form a url query parameters)
    resolveId(source: string, importer: string | undefined, options: any) {
        if (source.endsWith('.sql')) {
            const resolution = path.resolve(importer ? path.dirname(importer) : process.cwd(), source);
            const attributes = options?.attributes || options?.importAttributes || {};
            if (Object.keys(attributes).length > 0) {
                const queryParams = new URLSearchParams(attributes).toString();
                return `${resolution}?${queryParams}`;
            }

            return resolution;
        }
        return null;
    },

    // implement sql plugin
    async transform(code: string, id: string) {
        if (!id.includes('.sql')) return null;

        // extract import attribues
        const [filePath, queryString] = id.split('?');
        const queryParams = new URLSearchParams(queryString || '');
        const withAttributes: Record<string, string> = {};
        queryParams.forEach((value, key) => {
            withAttributes[key] = value;
        });

        // call sqlPlugin
        return {
            code: await loadSqlFile(filePath, withAttributes),
            map: null,
        };
    },
};

export default defineConfig({
    plugins: [vitestSqlPlugin],
    resolve: { tsconfigPaths: true },
    test: {
        globals: true,
        environment: 'node',
        silent: true,
        reporters: [
            'default',
            ['github-actions', { jobSummary: { enabled: false } }],
            ['junit', { outputFile: 'build/test-results/data-web.xml' }],
        ],
        coverage: {
            exclude: [
                'tests',
                '*.sql'
            ]
        }
    }
});
