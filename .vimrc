set number		
set showmatch		
set background=dark
 
set autoindent		
set smartindent
set expandtab
set shiftwidth=4
set softtabstop=4
set tabstop=4

au BufNewFile ~/*.c 0r ~/.base.c
au BufNewFile ~/*.cpp 0r ~/.base.cpp
au BufNewFile ~/*.html 0r ~/.base.html

if has("autocmd")
  au BufReadPost * if line("'\"") > 0 && line("'\"") <= line("$")
    \| exe "normal! g'\"" | endif
endif
