import random
import sys

def gerar_teste(perfil="misto", modo="T", num_itens=3000, num_atributos=300, num_aventureiros=100, num_ops=15000):
    # 1. Define e fixa o modo inicial (E T ou E L)
    print(f"E {modo}")
    
    # 2. Cadastro de Atributos
    for t in range(num_atributos):
        print(f"A Atributo_{t}")
        
    # 3. Cadastro de Itens
    for n in range(num_itens):
        print(f"I Item_{n}")
        
    # 4. Cadastro de Aventureiros
    for h in range(num_aventureiros):
        print(f"H Aventureiro_{h}")
        
    celulas_existentes = set()
    
    # Popula 10% da matriz inicial para ter dados consistentes nas consultas
    num_inicial = int(num_itens * num_atributos * 0.1)
    for _ in range(num_inicial):
        it = random.randint(0, num_itens - 1)
        at = random.randint(0, num_atributos - 1)
        val = random.randint(-15, 25)
        celulas_existentes.add((it, at))
        print(f"M {it} {at} {val}")

    for op in range(num_ops):
        # Seleção de comandos baseada no perfil
        # Nota: Se o perfil não for 'migracao', o comando 'E' é excluído para o modo ficar fixo.
        if perfil == "atualizacao":
            escolha = random.choices(["M", "F", "Z", "D", "LI", "Q"], weights=[65, 15, 5, 5, 5, 5])[0]
        elif perfil == "consulta":
            escolha = random.choices(["LI", "LA", "LH", "Q", "M"], weights=[30, 30, 15, 15, 10])[0]
        elif perfil == "migracao":
            escolha = random.choices(["M", "LI", "LA", "Q", "E"], weights=[30, 20, 20, 20, 10])[0]
        else: # misto (sem o 'E' para o modo continuar fixo)
            escolha = random.choices(["M", "LI", "LA", "LH", "Q", "F", "Z", "D"], weights=[30, 15, 15, 10, 10, 10, 5, 5])[0]

        if escolha == "M":
            it = random.randint(0, num_itens - 1)
            at = random.randint(0, num_atributos - 1)
            if celulas_existentes and random.random() < 0.2:
                it, at = random.choice(list(celulas_existentes))
                val = 0
                celulas_existentes.discard((it, at))
            else:
                val = random.randint(-20, 30)
                if val != 0:
                    celulas_existentes.add((it, at))
            print(f"M {it} {at} {val}")
            
        elif escolha == "LI":
            it = random.randint(0, num_itens - 1)
            print(f"LI {it}")
            
        elif escolha == "LA":
            at = random.randint(0, num_atributos - 1)
            print(f"LA {at}")
            
        elif escolha == "LH":
            av = random.randint(0, num_aventureiros - 1)
            print(f"LH {av}")
            
        elif escolha == "Q":
            av = random.randint(0, num_aventureiros - 1)
            n_recom = random.randint(1, min(5, num_itens))
            m_metricas = random.randint(1, 3)
            pesos = " ".join([str(random.randint(100, 500)) for _ in range(m_metricas)])
            print(f"Q {av} {n_recom} {m_metricas} {pesos}")
            
        elif escolha == "F":
            av = random.randint(0, num_aventureiros - 1)
            it = random.randint(0, num_itens - 1)
            print(f"F {av} {it}")
            
        elif escolha == "Z":
            turnos = random.randint(1, 5)
            print(f"Z {turnos}")
            
        elif escolha == "D":
            av = random.randint(0, num_aventureiros - 1)
            print(f"D {av}")
            
        elif escolha == "E": # Apenas executado se o perfil for explicitamente 'migracao'
            novo_modo = random.choice(["T", "L"])
            print(f"E {novo_modo}")

if __name__ == "__main__":
    # Uso: python3 gerador_experimental.py [perfil] [modo]
    # Exemplo: python3 gerador_experimental.py consulta T
    tipo_perfil = sys.argv[1] if len(sys.argv) > 1 else "misto"
    modo_fixo = sys.argv[2] if len(sys.argv) > 2 else "T"
    gerar_teste(perfil=tipo_perfil, modo=modo_fixo)