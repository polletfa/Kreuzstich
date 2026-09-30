/*
  Kreuzstich
  Copyright (c) 2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { defineConfig } from 'vitest/config'
import fs from 'fs/promises';
import path from 'path';
import loadSqlFile from './sqlPlugin';
import { walk } from 'estree-walker';

const vitestSqlPlugin = {
    name: 'vitest-sql-loader-with-attributes',

    async transform(code: string, id: string) {
        // vitest strip the import attributes so we need a workaround:
        // - we search the importing files for imports with attributes and replace them by using query parameters instead (?param=value)
        if (/\.(js|ts|jsx|tsx|mts)$/.test(id) && code.includes('.sql')) {
            const replacements: {
                index: number,
                length: number,
                replacement: string
            }[] = [];

            // parse and "walk" nodes
            const ast = this.parse(code);
            walk(ast, {
                enter(node: any) {
                    // sql imports with attributes
                    if (node.type === 'ImportDeclaration' && node.source.value.includes('.sql') && Array.isArray(node.attributes) && node.attributes.length > 0) {
                        const attributes: Record<string, string> = {};
                        for (const attr of node.attributes) {
                            attributes[attr.key.name] = attr.value.value;
                        }

                        replacements.push({
                            index: node.source.start,
                            length: node.end - node.source.start,
                            replacement: `"${node.source.value}?${new URLSearchParams(attributes).toString()}";`
                        });
                    }
                }
            });
            // replace from end to start (to avoid index shifting on replace)
            if(replacements.length>0) {
                const sorted = replacements.sort((a,b) => b.index - a.index);
                for(const repl of sorted) {
                    code = code.slice(0, repl.index) + repl.replacement + code.slice(repl.index + repl.length);
                }
                return {code, map: null};
            }
        }

        // Now we can intercept *.sql imports
        if (id.includes('.sql?') || id.endsWith('.sql')) {
            const [filePath, queryString] = id.split('?');
            const withAttributes = Object.fromEntries(new URLSearchParams(queryString || '').entries());

            return {
                code: await loadSqlFile(filePath, withAttributes),
                map: null,
            };
        }

        return null;
    }
};

export default defineConfig({
    plugins: [vitestSqlPlugin],
    resolve: { tsconfigPaths: true },
    test: {
        globals: true,
        environment: 'node',
        silent: true,
        reporters: [
            'tree',
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
