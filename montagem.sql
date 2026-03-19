CREATE TABLE Cliente (
    cpf CHAR(11) PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    estado_civil VARCHAR(50)
);

CREATE TABLE Inquilino(
    cpf_inquilino CHAR(11) PRIMARY KEY,
    profissao VARCHAR(100),
    renda DECIMAL(10, 2),
    FOREIGN KEY (cpf_inquilino) REFERENCES Cliente(cpf)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Proprietario_imvl (
    cpf_proprietario CHAR(11) PRIMARY KEY,
    ri_num VARCHAR(50) NOT NULL,
    ri_data DATE NOT NULL,
    FOREIGN KEY (cpf_proprietario) REFERENCES Cliente(cpf)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Corretor (
    creci CHAR(20) PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    data_vinculo DATE NOT NULL,
    comissao DECIMAL(5, 2)
);

CREATE TABLE Imovel (
    id INT AUTO_INCREMENT PRIMARY KEY,
    endereco VARCHAR(200) NOT NULL,
    area_m2 DECIMAL(10, 2),
    numero_comodos INT,
    numero_vagas INT,
    valor_aluguel DECIMAL(10, 2),
    data_oferta DATE NOT NULL,
    cpf_proprietario CHAR(11) NOT NULL,
    FOREIGN KEY (cpf_proprietario) REFERENCES Proprietario_imvl(cpf_proprietario)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Proposta (
    id INT AUTO_INCREMENT PRIMARY KEY,
    valor_proposta DECIMAL(10, 2) NOT NULL,
    data_proposta DATE NOT NULL,
    validade_proposta DATE NOT NULL,
    id_imovel INT NOT NULL,
    FOREIGN KEY (id_imovel) REFERENCES Imovel(id)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Visita (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cpf_inquilino CHAR(11) NOT NULL,
    id_imovel INT NOT NULL,
    FOREIGN KEY (cpf_inquilino) REFERENCES Inquilino(cpf_inquilino)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (id_imovel) REFERENCES Imovel(id)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Acompanha (
    id INT AUTO_INCREMENT PRIMARY KEY,
    creci_corretor CHAR(20) NOT NULL,
    id_imovel INT NOT NULL,
    FOREIGN KEY (creci_corretor) REFERENCES Corretor(creci)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (id_imovel) REFERENCES Imovel(id)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Telefone_Cliente (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cpf_cliente CHAR(11) NOT NULL,
    telefone VARCHAR(15) NOT NULL,
    FOREIGN KEY (cpf_cliente) REFERENCES Cliente(cpf)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Telefone_Corretor (
    id INT AUTO_INCREMENT PRIMARY KEY,
    creci_corretor CHAR(20) NOT NULL,
    telefone VARCHAR(15) NOT NULL,
    FOREIGN KEY (creci_corretor) REFERENCES Corretor(creci)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Fiador (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL, 
    cpf_inquilino CHAR(11) NOT NULL,
    FOREIGN KEY (cpf_inquilino) REFERENCES Inquilino(cpf_inquilino)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Telefone_Fiador (
    id INT AUTO_INCREMENT PRIMARY KEY,
    id_fiador INT NOT NULL,
    telefone VARCHAR(15) NOT NULL,
    FOREIGN KEY (id_fiador) REFERENCES Fiador(id)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE Contrato (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cpf_inquilino CHAR(11) NOT NULL,
    cpf_proprietario CHAR(11) NOT NULL,
    id_imovel INT NOT NULL,
    id_proposta INT NOT NULL,
    data_inicio DATE NOT NULL,
    data_fim DATE NOT NULL,
    valor_aluguel DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (cpf_inquilino) REFERENCES Inquilino(cpf_inquilino)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (cpf_proprietario) REFERENCES Proprietario_imvl(cpf_proprietario)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (id_imovel) REFERENCES Imovel(id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (id_proposta) REFERENCES Proposta(id)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);


-- Populando o Banco de Dados

-- Tabela Cliente
INSERT INTO Cliente (cpf, nome, estado_civil) VALUES
('12345678901', 'João Silva', 'Solteiro'),
('98765432109', 'Maria Oliveira', 'Casado'),
('45678912300', 'Pedro Santos', 'Divorciado'),
('65432198765', 'Ana Souza', 'Viúvo');

-- Tabela Inquilino
INSERT INTO Inquilino (cpf_inquilino, profissao, renda) VALUES
('12345678901', 'Engenheiro', 7500.00),
('98765432109', 'Professora', 3500.00);

-- Tabela Proprietario_imvl
INSERT INTO Proprietario_imvl (cpf_proprietario, ri_num, ri_data) VALUES
('45678912300', 'RI123456', '2023-01-15'),
('65432198765', 'RI987654', '2022-07-20');

-- Tabela Corretor
INSERT INTO Corretor (creci, nome, data_vinculo, comissao) VALUES
('C12345', 'Carlos Pereira', '2020-05-10', 5.00),
('C67890', 'Fernanda Lima', '2019-08-25', 4.50);

-- Tabela Imovel
INSERT INTO Imovel (endereco, area_m2, numero_comodos, numero_vagas, valor_aluguel, data_oferta, cpf_proprietario) VALUES
('Rua das Flores, 123', 80.0, 3, 2, 1500.00, '2023-12-01', '45678912300'),
('Av. Paulista, 987', 120.0, 4, 1, 2500.00, '2023-11-15', '65432198765');

-- Tabela Proposta
INSERT INTO Proposta (valor_proposta, data_proposta, validade_proposta, id_imovel) VALUES
(1400.00, '2023-12-05', '2023-12-20', 1),
(2400.00, '2023-11-20', '2023-12-05', 2);

-- Tabela Visita
INSERT INTO Visita (cpf_inquilino, id_imovel) VALUES
('12345678901', 1),
('98765432109', 2);

-- Tabela Acompanha
INSERT INTO Acompanha (creci_corretor, id_imovel) VALUES
('C12345', 1),
('C67890', 2);

-- Tabela Telefone_Cliente
INSERT INTO Telefone_Cliente (cpf_cliente, telefone) VALUES
('12345678901', '11987654321'),
('98765432109', '11876543210'),
('45678912300', '11965432187'),
('65432198765', '11954321678');

-- Tabela Telefone_Corretor
INSERT INTO Telefone_Corretor (creci_corretor, telefone) VALUES
('C12345', '11912345678'),
('C67890', '11987654321');

-- Tabela Fiador
INSERT INTO Fiador (nome, cpf_inquilino) VALUES
('Ricardo Lima', '12345678901'),
('Juliana Rocha', '98765432109');

-- Tabela Telefone_Fiador
INSERT INTO Telefone_Fiador (id_fiador, telefone) VALUES
(1, '11987651234'),
(2, '11965437890');

-- Tabela Contrato
INSERT INTO Contrato (cpf_inquilino, cpf_proprietario, id_imovel, id_proposta, data_inicio, data_fim, valor_aluguel) VALUES
('12345678901', '45678912300', 1, 1, '2024-01-01', '2024-12-31', 1400.00),
('98765432109', '65432198765', 2, 2, '2024-02-01', '2025-01-31', 2400.00);
