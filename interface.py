import tkinter as tk
from tkinter import messagebox
from tkinter import scrolledtext
from tkinter import simpledialog
import subprocess
import threading

def executar_comando(opcao, parametros=None):
    def executar():
        try:
            comando = ["./corretora", str(opcao)]
            if parametros:
                comando.extend(parametros)

            print(f"Comando: {comando}")

            resultado = subprocess.Popen(comando, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

            stdout, stderr = resultado.communicate()

            if resultado.returncode != 0:
                print(f"Erro ao executar comando: {stderr}") 
                messagebox.showerror("Erro", f"Erro ao executar a operação: {stderr}")
            else:
                print(f"Comando executado com sucesso. Resultado: {stdout}")
                exibir_resultado(stdout)
        except Exception as e:
            print(f"Erro inesperado: {e}") 
            messagebox.showerror("Erro", f"Erro ao executar a operação: {e}")

    thread = threading.Thread(target=executar)
    thread.start()

def exibir_resultado(texto):
    janela_resultado = tk.Toplevel() 
    janela_resultado.title("Resultado da Operação")
    
    texto_saida = scrolledtext.ScrolledText(janela_resultado, wrap=tk.WORD, width=125, height=20)
    texto_saida.pack(padx=10, pady=10)
    
    texto_saida.insert(tk.END, texto)
    texto_saida.config(state=tk.DISABLED)

def pedir_ano_rendimento():
    ano = simpledialog.askstring("Ano", "Digite o ano para verificar o rendimento:")
    if ano:
        executar_comando(4, [ano])

def pedir_imovel():
    imovel = simpledialog.askstring("Imóvel", "Digite o código do imóvel para listar as ofertas:")
    if imovel:
        executar_comando(3, [imovel])

def inserir_corretor():
    creci = simpledialog.askstring("Inserir Corretor", "Digite o CRECI do corretor:")
    nome = simpledialog.askstring("Inserir Corretor", "Digite o nome do corretor:")
    comissao = simpledialog.askstring("Inserir Corretor", "Digite a comissão do corretor:")
    data_vinculo = simpledialog.askstring("Inserir Corretor", "Digite a data de vínculo (YYYY-MM-DD):")

    if creci and nome and comissao and data_vinculo:
        executar_comando(11, ["1", creci, nome, comissao, data_vinculo])

def inserir_cliente():
    cpf = simpledialog.askstring("Inserir Cliente", "Digite o CPF do cliente:")
    nome = simpledialog.askstring("Inserir Cliente", "Digite o nome do cliente:")
    estado_civil = simpledialog.askstring("Inserir Cliente", "Digite o estado civil do cliente:")

    if cpf and nome and estado_civil:
        executar_comando(11, ["2", cpf, nome, estado_civil])

def inserir_imovel():
    cpf_proprietario = simpledialog.askstring("Inserir Imóvel", "Digite o CPF do proprietário:")
    endereco = simpledialog.askstring("Inserir Imóvel", "Digite o endereço do imóvel:")
    area_m2 = simpledialog.askstring("Inserir Imóvel", "Digite a área (m²) do imóvel:")
    numero_comodos = simpledialog.askstring("Inserir Imóvel", "Digite o número de cômodos:")
    numero_vagas = simpledialog.askstring("Inserir Imóvel", "Digite o número de vagas:")
    valor_aluguel = simpledialog.askstring("Inserir Imóvel", "Digite o valor do aluguel:")
    data_oferta = simpledialog.askstring("Inserir Imóvel", "Digite a data de oferta (YYYY-MM-DD):")

    if (cpf_proprietario and endereco and area_m2 and numero_comodos and 
        numero_vagas and valor_aluguel and data_oferta):
        executar_comando(11, ["3", cpf_proprietario, endereco, area_m2, numero_comodos, 
                             numero_vagas, valor_aluguel, data_oferta])

def atualizar_corretor():
    creci = simpledialog.askstring("Atualizar Corretor", "Digite o CRECI do corretor:")
    nome = simpledialog.askstring("Atualizar Corretor", "Digite o novo nome:")
    comissao = simpledialog.askstring("Atualizar Corretor", "Digite a nova comissão:")
    data_vinculo = simpledialog.askstring("Atualizar Corretor", "Digite a nova data de vínculo (YYYY-MM-DD):")

    if creci and nome and comissao and data_vinculo:
        executar_comando(11, ["4", creci, nome, comissao, data_vinculo]) 

def atualizar_cliente():
    cpf = simpledialog.askstring("Atualizar Cliente", "Digite o CPF do cliente:")
    nome = simpledialog.askstring("Atualizar Cliente", "Digite o novo nome:")
    estado_civil = simpledialog.askstring("Atualizar Cliente", "Digite o novo estado civil:")

    if cpf and nome and estado_civil:
        executar_comando(11, ["5", cpf, nome, estado_civil]) 

def atualizar_imovel():
    id_imovel = simpledialog.askstring("Atualizar Imóvel", "Digite o ID do imóvel:")
    endereco = simpledialog.askstring("Atualizar Imóvel", "Digite o novo endereço:")
    area_m2 = simpledialog.askstring("Atualizar Imóvel", "Digite a nova área (m²):")
    numero_comodos = simpledialog.askstring("Atualizar Imóvel", "Digite o novo número de cômodos:")
    numero_vagas = simpledialog.askstring("Atualizar Imóvel", "Digite o novo número de vagas:")
    valor_aluguel = simpledialog.askstring("Atualizar Imóvel", "Digite o novo valor do aluguel:")

    if (id_imovel and endereco and area_m2 and numero_comodos and 
        numero_vagas and valor_aluguel):
        executar_comando(11, ["6", id_imovel, endereco, area_m2, numero_comodos, 
                             numero_vagas, valor_aluguel]) 

def deletar_corretor():
    creci = simpledialog.askstring("Deletar Corretor", "Digite o CRECI do corretor:")
    if creci:
        executar_comando(11, ["7", creci]) 

def deletar_cliente():
    cpf = simpledialog.askstring("Deletar Cliente", "Digite o CPF do cliente:")
    if cpf:
        executar_comando(11, ["8", cpf])

def deletar_imovel():
    id_imovel = simpledialog.askstring("Deletar Imóvel", "Digite o ID do imóvel:")
    if id_imovel:
        executar_comando(11, ["9", id_imovel])

def abrir_janela_editar_banco():
    janela_editar = tk.Toplevel()
    janela_editar.title("Editar Banco de Dados")
    janela_editar.geometry("400x600")

    def voltar():
        janela_editar.destroy()

    botao1 = tk.Button(janela_editar, text="Inserir Corretor", command=inserir_corretor)
    botao1.pack(pady=10)

    botao2 = tk.Button(janela_editar, text="Inserir Cliente", command=inserir_cliente)
    botao2.pack(pady=10)

    botao3 = tk.Button(janela_editar, text="Inserir Imóvel", command=inserir_imovel)
    botao3.pack(pady=10)

    botao4 = tk.Button(janela_editar, text="Atualizar Corretor", command=atualizar_corretor)
    botao4.pack(pady=10)

    botao5 = tk.Button(janela_editar, text="Atualizar Cliente", command=atualizar_cliente)
    botao5.pack(pady=10)

    botao6 = tk.Button(janela_editar, text="Atualizar Imóvel", command=atualizar_imovel)
    botao6.pack(pady=10)

    botao7 = tk.Button(janela_editar, text="Deletar Corretor", command=deletar_corretor)
    botao7.pack(pady=10)

    botao8 = tk.Button(janela_editar, text="Deletar Cliente", command=deletar_cliente)
    botao8.pack(pady=10)

    botao9 = tk.Button(janela_editar, text="Deletar Imóvel", command=deletar_imovel)
    botao9.pack(pady=10)

    botao_voltar = tk.Button(janela_editar, text="Voltar", command=voltar)
    botao_voltar.pack(pady=10)

def abrir_janela_principal():
    root = tk.Tk()
    root.title("Sistema de Corretores e Imóveis")
    root.geometry("400x600")

    botao1 = tk.Button(root, text="Clientes com Propostas", command=lambda: executar_comando(1))
    botao1.pack(pady=10)

    botao2 = tk.Button(root, text="Imóveis Cadastrados", command=lambda: executar_comando(2))
    botao2.pack(pady=10)

    botao3 = tk.Button(root, text="Listar Ofertas por Imóvel", command=pedir_imovel)
    botao3.pack(pady=10)

    botao4 = tk.Button(root, text="Corretor com Maior Rendimento", command=pedir_ano_rendimento)
    botao4.pack(pady=10)

    botao5 = tk.Button(root, text="Imóveis Mais Caros", command=lambda: executar_comando(5))
    botao5.pack(pady=10)

    botao6 = tk.Button(root, text="Listar Proprietários", command=lambda: executar_comando(6))
    botao6.pack(pady=10)

    botao7 = tk.Button(root, text="Listar Inquilinos", command=lambda: executar_comando(7))
    botao7.pack(pady=10)

    botao8 = tk.Button(root, text="Listar Visitas Agendadas", command=lambda: executar_comando(8))
    botao8.pack(pady=10)

    botao9 = tk.Button(root, text="Listar Corretores por Imóvel", command=lambda: executar_comando(9))
    botao9.pack(pady=10)

    botao10 = tk.Button(root, text="Listar Contratos Vigentes", command=lambda: executar_comando(10))
    botao10.pack(pady=10)

    botao11 = tk.Button(root, text="Editar Banco de Dados", command=abrir_janela_editar_banco)
    botao11.pack(pady=10)

    root.mainloop()

abrir_janela_principal()