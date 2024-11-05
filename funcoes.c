int posicaoPontoVirgula(char *string) {
    for(int i = 0; i < sizeof(string)/sizeof(char); i++) {
        if(string[i] == ';') {
            return i;
        }
    }
}