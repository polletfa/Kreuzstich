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
