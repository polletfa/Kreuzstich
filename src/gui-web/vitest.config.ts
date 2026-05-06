/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
import { defineConfig } from 'vitest/config'

export default defineConfig({
    test: {
        silent: true,
        reporters: [
            'default',
            ['github-actions', { jobSummary: { enabled: false } }],
            ['junit', { outputFile: 'build/test-results/gui-web.xml' }],
        ],
    }
});
