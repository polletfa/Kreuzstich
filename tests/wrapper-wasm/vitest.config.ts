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
            exclude: [
                'wrapper-wasm.js'
            ]
        }
    },
});
