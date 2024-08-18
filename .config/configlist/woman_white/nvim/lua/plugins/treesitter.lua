require("nvim-treesitter.configs").setup {
  ensure_installed = { "markdown", "rust", "lua", "python", "css", "jsonc", "json", "toml" },
  sync_install = false,
  auto_install = false,
  highlight = {
    enable = true,
  },
}
