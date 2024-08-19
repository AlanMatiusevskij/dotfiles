local builtin = require "telescope.builtin"
vim.g.mapleader = " "

vim.keymap.set("i", "jk", "<esc>", { noremap = true })
vim.keymap.set("n", "<leader>w", ":w<CR>")
vim.keymap.set("n", "<leader>ff", builtin.find_files, {})
vim.keymap.set("n", "<leader>fg", builtin.live_grep, {})
vim.keymap.set("n", "<leader>fb", ":Telescope file_browser<CR>")
-- vim.keymap.set('n', '<leader>fh', builtin.help_tags, {})
vim.keymap.set("n", "<leader>q", ":q<CR>")
