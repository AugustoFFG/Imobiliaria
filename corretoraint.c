#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void conectarBanco(MYSQL *con) {
    if (mysql_real_connect(con, "localhost", "root", "password123", "corretorabd", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Erro ao conectar ao banco: %s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
}

void consultarClientesComPropostas(MYSQL *con) {
    char *query = 
        "SELECT DISTINCT Cliente.cpf, Cliente.nome, Cliente.estado_civil "
        "FROM Cliente "
        "INNER JOIN Inquilino ON Cliente.cpf = Inquilino.cpf_inquilino "
        "INNER JOIN Contrato ON Contrato.cpf_inquilino = Inquilino.cpf_inquilino "
        "INNER JOIN Proposta ON Proposta.id = Contrato.id_proposta;";

    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(con);

    MYSQL_ROW linha;
    int contador = 1;
    while ((linha = mysql_fetch_row(resultado))) {
        printf("Cliente %d:\n", contador);
        printf("Nome: %s, CPF: %s.\n", linha[1], linha[0]);
        printf("_____________________________________________________________________________________________________________________________\n");
        contador++;
    }

    mysql_free_result(resultado);
}

void consultarImoveisCadastrados(MYSQL *con) {
    char *query = 
        "SELECT Imovel.id, Imovel.endereco, Imovel.area_m2, Imovel.numero_comodos, "
        "Imovel.numero_vagas, Imovel.valor_aluguel, Imovel.data_oferta "
        "FROM Imovel;";
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(con);

    MYSQL_ROW linha;
    int contador = 1;
    while ((linha = mysql_fetch_row(resultado))) {
        printf("Imóvel %d:\n", contador);
        printf("ID: %s, Endereço: %s, Área: %s m², Cômodos: %s, Vagas: %s, Valor Aluguel: R$ %s, Data Oferta: %s.\n", 
               linha[0], linha[1], linha[2], linha[3], linha[4], linha[5], linha[6]);
        printf("_____________________________________________________________________________________________________________________________\n");
        contador++;
    }

    mysql_free_result(resultado);
}

void listarOfertasPorImovel(MYSQL *con, int id_imovel) {
    char query[256];
    snprintf(query, sizeof(query), 
        "SELECT Proposta.id, Proposta.valor_proposta, Proposta.data_proposta, Proposta.validade_proposta "
        "FROM Proposta WHERE Proposta.id_imovel = %d;", id_imovel);
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(con);

    MYSQL_ROW linha;
    int contador = 1;
    while ((linha = mysql_fetch_row(resultado))) {
        printf("Oferta %d:\n", contador);
        printf("ID Proposta: %s, Valor: R$ %s, Data Proposta: %s, Validade: %s.\n", 
               linha[0], linha[1], linha[2], linha[3]);
        printf("_____________________________________________________________________________________________________________________________\n");
        contador++;
    }

    mysql_free_result(resultado);
}

void corretorMaiorRendimento(MYSQL *con, int ano) {
    char query[512];
    snprintf(query, sizeof(query), 
        "SELECT Corretor.creci, Corretor.nome, SUM(Rendimento_corretor.comissao_recebida) AS rendimento "
        "FROM Corretor "
        "INNER JOIN Rendimento_corretor ON Corretor.creci = Rendimento_corretor.creci_corretor "
        "WHERE Rendimento_corretor.ano = %d "
        "GROUP BY Corretor.creci, Corretor.nome "
        "ORDER BY rendimento DESC "
        "LIMIT 1;", ano);

    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(con);

    MYSQL_ROW linha;
    if ((linha = mysql_fetch_row(resultado))) {
        printf("Corretor com maior rendimento em %d:\n", ano);
        printf("Creci: %s, Nome: %s, Rendimento: R$ %s.\n", linha[0], linha[1], linha[2]);
        printf("_____________________________________________________________________________________________________________________________\n");
    }
    else printf("Nenhum resultadoado encontrado para o ano %d.\n", ano);
    
    mysql_free_result(resultado);
}

void imoveisMaisCaros(MYSQL *con) {
    char *query = 
        "SELECT Imovel.id, Imovel.endereco, Imovel.valor_aluguel "
        "FROM Imovel ORDER BY Imovel.valor_aluguel DESC LIMIT 3;";
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(con);

    MYSQL_ROW linha;
    int contador = 1;
    while ((linha = mysql_fetch_row(resultado))) {
        printf("Imóvel %d:\n", contador);
        printf("ID: %s, Endereço: %s, Valor Aluguel: R$ %s.\n", linha[0], linha[1], linha[2]);
        printf("_____________________________________________________________________________________________________________________________\n");
        contador++;
    }

    mysql_free_result(resultado);
}

void listarProprietarios(MYSQL *con) {
    char *query = 
        "SELECT Proprietario_imvl.cpf_proprietario, Cliente.nome, Proprietario_imvl.ri_num, Proprietario_imvl.ri_data "
        "FROM Proprietario_imvl "
        "INNER JOIN Cliente ON Proprietario_imvl.cpf_proprietario = Cliente.cpf;";

    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(con);

    MYSQL_ROW linha;
    int contador = 1;
    while ((linha = mysql_fetch_row(resultado))) {
        printf("Proprietário %d:\n", contador);
        printf("CPF: %s, Nome: %s, RI: %s, Data RI: %s.\n", linha[0], linha[1], linha[2], linha[3]);
        printf("_____________________________________________________________________________________________________________________________\n");
        contador++;
    }

    mysql_free_result(resultado);
}

void listarInquilinos(MYSQL *con) {
    char *query = 
        "SELECT Inquilino.cpf_inquilino, Cliente.nome, Inquilino.profissao, Inquilino.renda "
        "FROM Inquilino "
        "INNER JOIN Cliente ON Inquilino.cpf_inquilino = Cliente.cpf;";

    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(con);

    MYSQL_ROW linha;
    int contador = 1;
    while ((linha = mysql_fetch_row(resultado))) {
        printf("Inquilino %d:\n", contador);
        printf("CPF: %s, Nome: %s, Profissão: %s, Renda: R$ %s.\n", linha[0], linha[1], linha[2], linha[3]);
        printf("_____________________________________________________________________________________________________________________________\n");
        contador++;
    }

    mysql_free_result(resultado);
}

void listarVisitasAgendadas(MYSQL *con) {
    char *query = 
        "SELECT Visita.id, Visita.cpf_inquilino, Cliente.nome, Visita.id_imovel, Imovel.endereco "
        "FROM Visita "
        "INNER JOIN Inquilino ON Visita.cpf_inquilino = Inquilino.cpf_inquilino "
        "INNER JOIN Cliente ON Inquilino.cpf_inquilino = Cliente.cpf "
        "INNER JOIN Imovel ON Visita.id_imovel = Imovel.id;";

    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(con);

    MYSQL_ROW linha;
    int contador = 1;
    while ((linha = mysql_fetch_row(resultado))) {
        printf("Visita %d:\n", contador);
        printf("ID Visita: %s, CPF Inquilino: %s, Nome Inquilino: %s, ID Imóvel: %s, Endereço Imóvel: %s.\n", 
               linha[0], linha[1], linha[2], linha[3], linha[4]);
        printf("_____________________________________________________________________________________________________________________________\n");
        contador++;
    }

    mysql_free_result(resultado);
}

void listarCorretoresPorImovel(MYSQL *con) {
    char *query = 
        "SELECT Acompanha.id_imovel, Imovel.endereco, Acompanha.creci_corretor, Corretor.nome "
        "FROM Acompanha "
        "INNER JOIN Imovel ON Acompanha.id_imovel = Imovel.id "
        "INNER JOIN Corretor ON Acompanha.creci_corretor = Corretor.creci;";

    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(con);

    MYSQL_ROW linha;
    int contador = 1;
    while ((linha = mysql_fetch_row(resultado))) {
        printf("Acompanhamento %d:\n", contador);
        printf("ID Imóvel: %s, Endereço: %s, CRECI Corretor: %s, Nome Corretor: %s.\n", 
               linha[0], linha[1], linha[2], linha[3]);
        printf("_____________________________________________________________________________________________________________________________\n");
        contador++;
    }

    mysql_free_result(resultado);
}

void listarContratosVigentes(MYSQL *con) {
    char *query = 
        "SELECT Contrato.id, Contrato.cpf_inquilino, Cliente.nome AS nome_inquilino, "
        "Contrato.cpf_proprietario, Proprietario_imvl.ri_num, Contrato.id_imovel, "
        "Imovel.endereco, Contrato.data_inicio, Contrato.data_fim, Contrato.valor_aluguel "
        "FROM Contrato "
        "INNER JOIN Inquilino ON Contrato.cpf_inquilino = Inquilino.cpf_inquilino "
        "INNER JOIN Cliente ON Inquilino.cpf_inquilino = Cliente.cpf "
        "INNER JOIN Proprietario_imvl ON Contrato.cpf_proprietario = Proprietario_imvl.cpf_proprietario "
        "INNER JOIN Imovel ON Contrato.id_imovel = Imovel.id "
        "WHERE Contrato.data_fim >= CURDATE();";

    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(con);

    MYSQL_ROW linha;
    int contador = 1;
    while ((linha = mysql_fetch_row(resultado))) {
        printf("Contrato %d:\n", contador);
        printf("ID Contrato: %s, CPF Inquilino: %s, Nome Inquilino: %s, CPF Proprietário: %s,\nRI Proprietário: %s, "
               "ID Imóvel: %s, Endereço Imóvel: %s, Data Início: %s, Data Fim: %s,\nValor Aluguel: R$ %s.\n", 
               linha[0], linha[1], linha[2], linha[3], linha[4], linha[5], linha[6], linha[7], linha[8], linha[9]);
        printf("_____________________________________________________________________________________________________________________________\n");
        contador++;
    }

    mysql_free_result(resultado);
}

void inserirCorretor(MYSQL *con, char *creci, char *nome, char *comissao, char *data_vinculo) {
    char query[512];
    snprintf(query, sizeof(query), 
        "INSERT INTO Corretor (creci, nome, data_vinculo, comissao) VALUES ('%s', '%s', '%s', %s);", 
        creci, nome, data_vinculo, comissao);
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na inserção do corretor: %s\n", mysql_error(con));
    }
    else printf("Corretor inserido com sucesso!\n");
}

void inserirCliente(MYSQL *con, char *cpf, char *nome, char *estado_civil) {
    char query[512];
    snprintf(query, sizeof(query), 
        "INSERT INTO Cliente (cpf, nome, estado_civil) VALUES ('%s', '%s', '%s');", 
        cpf, nome, estado_civil);
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na inserção do cliente: %s\n", mysql_error(con));
    }
    else printf("Cliente inserido com sucesso!\n");
}

void inserirImovel(MYSQL *con, char *cpf_proprietario, char *endereco, char *area_m2, char *numero_comodos, char *numero_vagas, char *valor_aluguel, char *data_oferta) {
    char query[512];
    snprintf(query, sizeof(query), 
        "INSERT INTO Imovel (endereco, area_m2, numero_comodos, numero_vagas, valor_aluguel, data_oferta, cpf_proprietario) "
        "VALUES ('%s', %s, %s, %s, %s, '%s', '%s');", 
        endereco, area_m2, numero_comodos, numero_vagas, valor_aluguel, data_oferta, cpf_proprietario);
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro na inserção do imóvel: %s\n", mysql_error(con));
    }
    else printf("Imóvel inserido com sucesso!\n");
}

void atualizarCorretor(MYSQL *con, char *creci, char *nome, char *comissao, char *data_vinculo) {
    char query[512];
    snprintf(query, sizeof(query), 
        "UPDATE Corretor SET nome = '%s', data_vinculo = '%s', comissao = %s WHERE creci = '%s';", 
        nome, data_vinculo, comissao, creci);
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro ao atualizar corretor: %s\n", mysql_error(con));
    }
    else printf("Corretor atualizado com sucesso!\n");
}

void atualizarCliente(MYSQL *con, char *cpf, char *nome, char *estado_civil) {
    char query[512];
    snprintf(query, sizeof(query), 
        "UPDATE Cliente SET nome = '%s', estado_civil = '%s' WHERE cpf = '%s';", 
        nome, estado_civil, cpf);
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro ao atualizar cliente: %s\n", mysql_error(con));
    }
    else printf("Cliente atualizado com sucesso!\n");
}

void atualizarImovel(MYSQL *con, char *id_imovel, char *endereco, char *area_m2, char *numero_comodos, 
                     char *numero_vagas, char *valor_aluguel) {
    char query[512];
    snprintf(query, sizeof(query), 
        "UPDATE Imovel SET endereco = '%s', area_m2 = %s, numero_comodos = %s, "
        "numero_vagas = %s, valor_aluguel = %s WHERE id = %s;", 
        endereco, area_m2, numero_comodos, numero_vagas, valor_aluguel, id_imovel);
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro ao atualizar imóvel: %s\n", mysql_error(con));
    } 
    else printf("Imóvel atualizado com sucesso!\n");
}

void deletarCorretor(MYSQL *con, char *creci) {
    char query[512];
    snprintf(query, sizeof(query), 
        "DELETE FROM Corretor WHERE creci = '%s';", creci);
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro ao deletar corretor: %s\n", mysql_error(con));
    } 
    else printf("Corretor deletado com sucesso!\n");
}

void deletarCliente(MYSQL *con, char *cpf) {
    char query[512];
    snprintf(query, sizeof(query), 
        "DELETE FROM Cliente WHERE cpf = '%s';", cpf);
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "Erro ao deletar cliente: %s\n", mysql_error(con));
    } 
    else printf("Cliente deletado com sucesso!\n");
}

void deletarImovel(MYSQL *con, char *id_imovel) {
    char query[512];
    snprintf(query, sizeof(query), 
        "DELETE FROM Imovel WHERE id = %s;", id_imovel);
    
    if (mysql_query(con, query)){
        fprintf(stderr, "Erro ao deletar imóvel: %s\n", mysql_error(con));
    } 
    else printf("Imóvel deletado com sucesso!\n");
}

void editarBanco(MYSQL *con, int opcao_editar, char **args) {
    switch (opcao_editar) {
        case 1:
            inserirCorretor(con, args[0], args[1], args[2], args[3]);
            break;
        case 2:
            inserirCliente(con, args[0], args[1], args[2]);
            break;
        case 3:
            inserirImovel(con, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
            break;
        case 4:
            atualizarCorretor(con, args[0], args[1], args[2], args[3]);
            break;
        case 5:
            atualizarCliente(con, args[0], args[1], args[2]);
            break;
        case 6:
            atualizarImovel(con, args[0], args[1], args[2], args[3], args[4], args[5]);
            break;
        case 7:
            deletarCorretor(con, args[0]);
            break;
        case 8:
            deletarCliente(con, args[0]);
            break;
        case 9:
            deletarImovel(con, args[0]);
            break;
        default:
            printf("Opção inválida!\n");
    }
}

int main(int argc, char *argv[]) {

    int opcao = atoi(argv[1]);

    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "Erro ao inicializar MySQL: %s\n", mysql_error(con));
        exit(1);
    }

    conectarBanco(con);

    switch (opcao) {
        case 1:
            consultarClientesComPropostas(con);
            break;
        case 2:
            consultarImoveisCadastrados(con);
            break;
        case 3:
            int id_imovel = atoi(argv[2]);
            listarOfertasPorImovel(con, id_imovel);
            break;
        case 4:
            int ano = atoi(argv[2]);
            corretorMaiorRendimento(con, ano);
            break;
        case 5:
            imoveisMaisCaros(con);
            break;
        case 6:
            listarProprietarios(con);
            break;
        case 7:
            listarInquilinos(con);
            break;
        case 8:
            listarVisitasAgendadas(con);
            break;
        case 9:
            listarCorretoresPorImovel(con);
            break;
        case 10:
            listarContratosVigentes(con);
            break;
        case 11:
            int opcao_editar = atoi(argv[2]);
            editarBanco(con, opcao_editar, argv + 3);
            break;
        default:
            printf("Opção inválida!\n");
    }

    mysql_close(con);
    return 0;
}