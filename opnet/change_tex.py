# coding:utf-8

"""
用来更改Sphinx生成的中文latex,从而使得其可结合xelatex来生成相应的中文Pdf
"""
utf8ttf = r"""
%%
%% This is file `utf8ttf.def',
%% 
%% This is a slightly modified version of 'utf8x.def' by Dominique Unruh
%% 
\ProvidesFile{utf8ttf.def}
   [2005/07/21 UTF-8 support using Truetype fonts for inputenc]
\expandafter\ifx\csname restore@utf@viii@actives\endcsname\relax\else
  \csname restore@utf@viii@actives\endcsname\expandafter\endinput\fi
\count255=\catcode`\@\catcode`\@11 %SPACE
\ifx\@gobble\undefined\def\@gobble#1{}\fi
\ifx\@gobbletwo\undefined\def\@gobbletwo#1#2{}\fi
\def\utf@viii@err#1{%
  \PackageError{utf8ttf}{Character \number#1 \uc@spc appeared alone}{%
    Characters 128-191 are only allowed as arguments to characters 194-244}}
\def\utf@viii@xnum#1#2\utf@viii@err#3#4\@nil{%
  \ifx\empty#3%
  \count#1=-1\relax
  \PackageError{utf8ttf}{Malformed UTF-8 sequence}{%
    If the character is an argument, put it in {}}\else
  \count#1=#3\fi}
\def\utf@viii@undef#1#2#3#4{%
  \begingroup
  \count0=#1\relax
  \ifx#3\@nil  % Two-byte sequences
  \expandafter\utf@viii@xnum\expandafter1#2\empty\empty\empty\empty\empty\empty\empty\empty\empty\utf@viii@err\empty\@nil
  \ifnum\count1=-1 \count0=192\count1="1007D\fi
  \multiply\count0by64\relax
  \advance\count0by\count1\relax
  \advance\count0by-12416\relax
  \else
  \ifx#4\@nil  % Three-byte sequences
  \expandafter\utf@viii@xnum\expandafter1#2\empty\empty\empty\empty\empty\empty\empty\empty\empty\utf@viii@err\empty\@nil
  \expandafter\utf@viii@xnum\expandafter2#3\empty\empty\empty\empty\empty\empty\empty\empty\empty\utf@viii@err\empty\@nil
  \ifnum\count1=-1 \count0=224\count1=128\count2="1007D\fi
  \ifnum\count2=-1 \count0=224\count1=128\count2="1007D\fi
  \multiply\count0by64\relax
  \advance\count0by\count1\relax
  \multiply\count0by64\relax
  \advance\count0by\count2\relax
  \advance\count0by-925824\relax
  \else  % Four-byte sequences
  \expandafter\utf@viii@xnum\expandafter1#2\empty\empty\empty\empty\empty\empty\empty\empty\empty\utf@viii@err\empty\@nil
  \expandafter\utf@viii@xnum\expandafter2#3\empty\empty\empty\empty\empty\empty\empty\empty\empty\utf@viii@err\empty\@nil
  \expandafter\utf@viii@xnum\expandafter3#4\empty\empty\empty\empty\empty\empty\empty\empty\empty\utf@viii@err\empty\@nil
  \ifnum\count1=-1 \count0=240\count1=128\count2=128\count3="1007D\fi
  \ifnum\count2=-1 \count0=240\count1=128\count2=128\count3="1007D\fi
  \ifnum\count3=-1 \count0=240\count1=128\count2=128\count3="1007D\fi
  \multiply\count0by64%
  \advance\count0by\count1%
  \multiply\count0by64%
  \advance\count0by\count2%
  \multiply\count0by64%
  \advance\count0by\count3%
  \advance\count0by-"3C82080\relax
  \fi\fi
  \begingroup\expandafter\utf@viii@map\expandafter{\number\count0}\endgroup
  \expandafter\endgroup
  \expandafter\unichar\expandafter{\number\count0}}%
\def\utf@viii@make#1#2#3#4#5#6{%
 \count255=#1\relax
 \loop\ifnum\count255<#2\relax
 \catcode\count255\active
 \begingroup
   \uccode`\~\count255%
   \uccode`\u`\u%
   \uppercase{%
 \endgroup
   \edef~%
 #3{\noexpand\expandafter\noexpand\ifx\noexpand\csname u8-\number\count255-#4\noexpand\endcsname\relax
   \begingroup
     \let\noexpand\utf@viii@undeferr
     \noexpand\@gobble\noexpand\empty\noexpand\empty
     \noexpand\empty\noexpand\empty\noexpand\@gobbletwo\relax\relax
     % ===
   \noexpand\expandafter\endgroup
   % If \let not executed: \utf@viii@undeferr is called
   % otherwise: \utf@viii@undef.
   \noexpand\utf@viii@undeferr{\noexpand\string\noexpand~\noexpand\string#6}%
     \noexpand\utf@viii@undef{\number\count255}#5%
 \noexpand\else
   \noexpand\expandafter\noexpand\unichar\noexpand\expandafter{%
     \noexpand\csname u8-\number\count255-#4\noexpand\endcsname}\noexpand\fi}}%
 \advance\count255by1\relax
 \repeat}%
\def\restore@utf@viii@actives{%
  \let\@inpenc@test\relax
  \utf@viii@make{194}{224}{####1}{\noexpand\string####1}{{####1}\noexpand\@nil\noexpand\@nil}{####1}%
  \utf@viii@make{224}{240}{####1####2}{\noexpand\string####1\noexpand\string####2}{{####1}{####2}\noexpand\@nil}{####1\noexpand\string####2}%
  \utf@viii@make{240}{245}{####1####2####3}{\noexpand\string####1\noexpand\string####2\noexpand\string####3}{{####1}{####2}{####3}}{####1\noexpand\string####2\noexpand\string####3}%
  \count255=128\relax
  \loop\ifnum\count255<192\relax
  \catcode\count255\active
  \begingroup
    \uccode`\~\count255 %SPACE
    \uppercase{%
  \endgroup
    \edef~}%
  {\noexpand\utf@viii@err{\number\count255}}%
 \advance\count255by1\relax
 \repeat}%
\def\utf@viii@map#1{%
  \begingroup
  \count0=#1\divide\count0by64\relax
  \ifnum#1<"80\relax
  % ASCII is not handled by utf8ttf.def
  \else\ifnum#1<"800\relax
    \count1=-\count0\multiply\count1by64\advance\count1by#1\relax
    \advance\count0by192\advance\count1by128\relax
    \begingroup
      \lccode`\B=\count1 %SPACE
      \lowercase{%
    \endgroup
      \expandafter\gdef\csname u8-\number\count0-B\endcsname}{#1}%
  \else\ifnum#1<"10000\relax
    \count2=-\count0\multiply\count2by64\advance\count2by#1\relax
    \divide\count0by64 %SPACE
    \count1=-\count0\multiply\count1by4096\advance\count1by#1%
    \divide\count1by64%
    \advance\count0by224\advance\count1by128\advance\count2by128 %SPACE
    \begingroup
      \lccode`\B=\count1 %SPACE
      \lccode`\C=\count2 %SPACE
      \lowercase{%
    \endgroup
      \expandafter\gdef\csname u8-\number\count0-BC\endcsname}{#1}%
  \else\ifnum#1<"110000 %SPACE
    \count3=-\count0\multiply\count3by64\advance\count3by#1\relax
    \divide\count0by64 %SPACE
    \count2=-\count0\multiply\count2by4096\advance\count2by#1%
    \divide\count2by64%
    \divide\count0by64 %SPACE
    \count1=-\count0\multiply\count1by262144\advance\count1by#1%
    \divide\count1by4096 %SPACE
    \advance\count0by240\advance\count1by128%
    \advance\count2by128\advance\count3by128 %SPACE
    \begingroup
      \lccode`\B=\count1 %SPACE
      \lccode`\C=\count2 %SPACE
      \lccode`\D=\count3 %SPACE
      \lowercase{%
    \endgroup
      \expandafter\gdef\csname u8-\number\count0-BCD\endcsname}{#1}%
  \else
    \PackageWarning{utf8ttf}{Invalid code position \number#1 \uc@spc
      defined,\MessageBreak unrepresentable in UTF-8}%
  \fi\fi\fi\fi
  \endgroup
}
\begingroup
  \lccode`\A=`\{\lccode`\B=`\}\lccode`\C=`\\%
  \lccode`\P=`\P\lccode`\U=`\U%
  \lowercase{%
\endgroup
  \def\utf@viii@undeferr#1#2#3#4#5#6{%
    \ifx\@gobble#1\else[Please insert CPrerenderUnicodeA#1B into preamble]\fi}}
\ifx\AtBeginDocument\undefined\else
  \ifx\@nodocument\relax\else
    \AtBeginDocument{%
    \begingroup
    \expandafter\def\expandafter\temp@a\expandafter#\expandafter1%
      \string\utf@viii@#2\@nil{%
        \ifx\@nil#2\@nil\count2\count0\else\count1\count0\fi}%
    \count0=128 \count1=0 \count2=0 %SPACE
    \loop\ifnum\count0<245 %SPACE
    \ifnum\count0=192 \advance\count0by2 \fi
    \lccode`\~\count0 %SPACE
    \ifnum\catcode\count0=13 %SPACE
      \lowercase{%
      \expandafter\expandafter\expandafter\temp@a\expandafter\meaning\expandafter~%
        \string\utf@viii@\@nil}%
    \else
      \count2\count0\fi
    \advance\count0by1 %SPACE
    \repeat
    \ifnum\count1=0 \else\ifnum\count2=0 \else
      \PackageWarning{utf8ttf.def}{Character(s) \number\count2\space\space
        etc. got redefined somewhere.\MessageBreak
        Restoring to its utf8ttf-meaning}%
      \aftergroup\restore@utf@viii@actives
    \fi\fi
    \endgroup}%
  \fi
\fi
\catcode`\@=\count255\relax
\csname restore@utf@viii@actives\endcsname
\ifx\unichar\undefined\def\unichar#1{%
      \PackageWarning{utf8ttf.def}{No Truetype font defined}}\fi
\endinput
"""

ttfucs = r"""
%%
%% Package 'ttfucs' to use Unicode through Truetype fonts
%%
%% Otfried Cheong
%% 
\ProvidesPackage{ttfucs}[2005/07/21 Using Unicode with Truetype fonts]

\def\Ipe@hexnumber@#1{\ifcase\number#1
  0\or 1\or 2\or 3\or 4\or 5\or 6\or 7\or 8\or
  9\or a\or b\or c\or d\or e\or f\fi}

%% \Ipe@family stores the current font family for Unicode characters,
%% \Ipe@plane is the subfont number in hex.

\def\Ipe@family{}
\def\Ipe@plane{}

%% The following macros are taken from the 'CJK' package
%% by Werner Lemberg (with names changed).

\def\Ipe@@empty#1{%
  \ifx\Ipe@plane\undefined\def\mandatory@arg{cmr10}\else
  \edef\mandatory@arg{\mandatory@arg\Ipe@plane}\fi%
  \empty@sfcnt#1%
  \xdef\font@name{\csname \curr@fontshape/\f@size/%
    \ifx\Ipe@plane\undefined\else\Ipe@plane\fi\endcsname}}

\DeclareSizeFunction{IpeUnicode}{\Ipe@@empty\@font@warning}

%% the auxiliary macro \Ipe@numbToHex converts number #2 into a hex string
%%     and assigns it globally to #1.

\def\Ipe@numbToHex#1#2{%
  {\count\z@ #2\relax
   \count\tw@ \count\z@
   \divide\count\z@ \sixt@@n
   \count@ \count\z@
   \multiply\count@ \sixt@@n
   \advance\count\tw@ -\count@
   \xdef#1{\Ipe@hexnumber@{\count\z@}\Ipe@hexnumber@{\count\tw@}}}}

% \IpeTTFchar typesets a Unicode character.

\def\IpeTTFchar#1{%
  \@tempcnta #1\relax
  \divide\@tempcnta by 256\relax
  \Ipe@numbToHex\Ipe@plane{\@tempcnta}%
  \multiply \@tempcnta by 256\relax
  \@tempcntb #1\relax
  \advance\@tempcntb by -\@tempcnta\relax
  {\Ipe@usefont\symbol{\@tempcntb}}}

\def\Ipe@usefont{\usefont{C70}{\Ipe@family}{m}{n}}

\def\TruetypeFont#1{%
  \renewcommand{\Ipe@family}{#1}%
  \renewcommand{\unichar}[1]{\IpeTTFchar{##1}}}

% The font encoding 'C70' is originally defined by the CJK package.

\begingroup
\nfss@catcodes
\gdef\DeclareTruetypeFont#1#2{%
  \def\Ipe@name{#1}
  \def\Ipe@@name{#2}
  \DeclareFontEncoding{C70}{}{}
  \DeclareFontSubstitution{C70}{\Ipe@name}{m}{n}
  \DeclareFontFamily{C70}{\Ipe@name}{\hyphenchar \font\m@ne}
  \DeclareFontShape{C70}{\Ipe@name}{m}{n}{<-> IpeUnicode * \Ipe@@name}{}
  \pdfmapfile{=#1.map}
  \TruetypeFont{#1}}
\gdef\DeclareTruetypeFontShape#1#2#3#4{%
  \def\Ipe@name{#1}
  \def\Ipe@@name{#4}
  \DeclareFontShape{C70}{\Ipe@name}{#2}{#3}{<-> IpeUnicode * \Ipe@@name}{}
  \def\Ipe@usefont{\usefont{C70}{\Ipe@family}{\f@series}{\f@shape}}}
\endgroup

\@onlypreamble\DeclareTruetypeFont

%% --------------------------------------------------------------------
"""

def create_file():
    """
    创建utf8ttf.def和ttfucs.sty两个文件
    """
    fh = open("utf8ttf.def", 'w')
    fh.write(utf8ttf)
    fh.close()
    fh = open("ttfucs.sty", "w")
    fh.write(ttfucs)
    fh.close()

def change():
    """
    更改对应的tex文档
    """
    import os
    import sys
    filename = ""
    if len(sys.argv) != 2:
        while filename == "":
            filename = raw_input("Enter the file's name to convert:")
    else:
        filename = sys.argv[1]
    while filename not in os.listdir(os.getcwd()):
        print "The name you offer doesn't exist!"
        filename = raw_input("Enter the file's name to convert:")
    fh = open(filename)
    cont = fh.read()
    fh.close()
    replace = """
\documentclass[letterpaper,10pt]{manual}
\usepackage[utf8ttf,utf8]{inputenc}
\usepackage{ttfucs}
\usepackage{CJKutf8}   %可以去掉
\usepackage[T1]{fontenc}
% \usepackage{babel}
\usepackage{times}
\usepackage[Bjarne]{fncychap}
\usepackage{sphinx}

\usepackage{hyperref}   % 书签
\usepackage{fontspec}   % 以下是xelatex的一些包
\usepackage{xunicode}
\usepackage{xltxtra}
\usepackage{verbatim}
\setsansfont{SimSun}  % 选择系统字体, fc-list查看
\setromanfont{SimSun}  % 选择系统字体, fc-list查看
\XeTeXlinebreaklocale "zh" 
\XeTeXlinebreakskip = 0pt plus 1pt
    """
    cont = cont.replace(cont[:cont.index(r"\title")], replace + "\n")
    fh = open(filename[:-4] + "_new" + ".tex", "w")
    fh.write(cont)
    fh.close()
    create_file()

if __name__ == "__main__":
    change()
