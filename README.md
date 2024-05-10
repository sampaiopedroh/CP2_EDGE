
Integrates: Felipe Alamino (555819), Davi Vieira (556789), Luca Monteiro (556906), Victor Henrique (558258), Pedro Sampaio (555613)
# CP2_EDGE - Projeto de IOT para Vinheria Agnello
-> Contextualização
A Vinheria Agnello solicitou a implementação de um sistema de monitoramento ambiental para garantir as condições ideais de armazenamento de seus vinhos. O projeto envolve a utilização de sensores para medir temperatura, umidade e intensidade de luz no ambiente, exibindo os resultados em um display LCD e acionando LEDs e um buzzer para alertar sobre possíveis desvios das condições ideais.

-> Explicação do Projeto
O código fornecido utiliza diversos componentes Arduino para realizar o monitoramento ambiental:
- Sensor DHT11: Mede a temperatura e umidade do ambiente.
- Display LCD: Exibe as informações de temperatura, umidade e intensidade de luz.
- LEDs RGB: Indicam visualmente as condições ambientais, com cores diferentes para cada faixa de valores.
- Sensor LDR: Mede a intensidade de luz no ambiente.
- Buzzer: Emite um som de alerta quando as condições ambientais estão fora do ideal.

-> O código é dividido em duas partes principais:
Setup: Inicializa os componentes, define os pinos de entrada e saída, e exibe uma mensagem de carregamento no display LCD.
Loop: Realiza as seguintes ações em um loop contínuo:
- Lê os valores dos sensores de temperatura, umidade e luz.
- Exibe as informações no display LCD, alternando entre a intensidade de luz, umidade e temperatura a cada 2 segundos.
- Acende os LEDs de acordo com os valores lidos, indicando se as condições estão dentro do ideal (verde), fora do ideal (vermelho) ou em uma faixa intermediária (amarelo).
- Aciona o buzzer quando as condições estão fora do ideal.
- Envia os valores lidos para a porta serial para monitoramento.
O código também inclui funções auxiliares para acender os LEDs nas cores desejadas, exibir as informações no display LCD e acionar o buzzer.

-> Conclusão
O projeto desenvolvido para a Vinheria Agnello utiliza tecnologia IOT para monitorar as condições ambientais do local de armazenamento dos vinhos. Ao medir temperatura, umidade e intensidade de luz, o sistema alerta sobre possíveis desvios das condições ideais, permitindo que ajustes sejam feitos para preservar a qualidade dos vinhos. A exibição das informações no display LCD e o uso de LEDs e buzzer facilitam a visualização e compreensão do estado ambiental, tornando o sistema eficiente e fácil de usar.
