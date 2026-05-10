/*
  Kreuzstich
  Copyright (c) 2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { defineConfig } from 'vitest/config'

export default defineConfig({
    test: {
        environment: 'node',
        reporters: [
            'default',
            ['github-actions', { jobSummary: { enabled: false } }],
            ['junit', { outputFile: 'test-results/wrapper-wasm.xml' }],
        ],
        coverage: {
            include: ['build/**/*.ts'],
            exclude: ['*.d.ts']
        }
    },
});
