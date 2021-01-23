@echo off
del Saida.count
del TesteListaDebug.log
TRAB4-2.exe /sTesteListaDebug.script /l>>TesteListaDebug.log
start TesteListaDebug.log