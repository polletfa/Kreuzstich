/*
  Kreuzstich
  Copyright (c) 2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { defineConfig } from 'vitest/config'
import tsconfigPaths from 'vite-tsconfig-paths';

export default defineConfig({
    plugins: [tsconfigPaths()],
    test: {
        environment: 'node',
        silent: true,
        reporters: [
            'default',
            ['github-actions', { jobSummary: { enabled: false } }],
            ['junit', { outputFile: 'build/test-results/data-web.xml' }],
        ],
        coverage: {
            exclude: [
                'build'
            ]
        }
    },
});
