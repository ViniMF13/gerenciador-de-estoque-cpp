## Classe: Item

- Responsável por criar um novo Item
- Armazenar as informações nome, valor e quantidade no estoque
- Atualizar os detalhes do item após validação bem-sucedida.
- Tratar situações de erro, como tentativas de inserção de informações inválidas.


## Classe: Inventário 

- Validar a entrada do usuário, incluindo nome, valor e quantidade do item a ser adicionado.
- Verificar se um item existe no inventário.
- Adicionar novo item ao inventário após validação bem sucedida.
- Remover item do inventário após validação bem sucedida
- Editar itens do inventario.
- Tratar situações de erro, como tentativas de inserção de informações inválidas.
- Buscar informações dos itens
- Exibir em tela uma lista em ordem alfabética de todos os itens do inventário

Colaboração: Item


## Classe: Interface

- Responsável por interagir com o usuário e apresentar informações no console.
- Exibir o menu de opções	
- Limpar a tela do console 
- Ler informações (como nomes e valores) do usuário
- Exibir o histórico de movimentação	

Colaboração: Inventário


## Classe: Movimentação

- Armazenar informações sobre uma movimentação, incluindo nome, tipo, quantidade e data.
- Converter as informações da movimentação em formato JSON.
- Fornecer informações específicas da movimentação quando solicitado.
- Obter o nome da movimentação.
- Obter o tipo da movimentação.
- Obter a quantidade da movimentação.
- Obter a data da movimentação.

Colaboração: Item , Inventário
