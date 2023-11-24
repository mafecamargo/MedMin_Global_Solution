# MedMin - Global Solution <br>

# Problema abordado: <br>
A gestão hospitalar enfrenta desafios significativos relacionados ao estoque, sendo essencial abordar tais questões para garantir um funcionamento eficiente. A complexidade do ambiente hospitalar, com seu intenso fluxo físico de medicamentos, materiais médicos, pacientes e documentos, destaca a importância de uma abordagem estratégica para a gestão de estoque. A necessidade de evitar faltas de produtos cruciais, otimizando simultaneamente os custos, ressalta a importância de adotar práticas de estoque inteligente.  <br>
Um estoque inteligente não apenas assegura a disponibilidade adequada de recursos, mas também contribui para o equilíbrio entre oferta e demanda, promovendo eficiência operacional e garantindo que o ambiente hospitalar esteja preparado para enfrentar os desafios dinâmicos inerentes à sua natureza complexa. <br>

# Objetivo do Produto: <br>
A MedMin nasceu para facilitar a gestão hospitalar com estoque inteligente e um aplicativo, em que conseguem ver as informações na palma da mão. Focado para os funcionários que trabalham na gestão, com a MedMin eles conseguem ver a temperatura e umidade do estoque, e ter uma ideia da quantidade de remédios a partir da distância deles.  <br>
Para maior praticidade, a MedMin alerta de forma sonora tanto no próprio estoque quanto no aplicativo quando a temperatura e a umidade estão fora do padrão. Além disso, alerta de forma luminosa no próprio estoque quando os remédios estão acabando, como estamos usando a distância da profundidade das prateleiras dentro do estoque, assim o sensor fica na ponta da prateleira e cada vez que um remédio é usado, a distância entre eles é maior. Logo quando maior a distância, maior o uso de determinado remédio; e quando menor a distância, menor o uso dele. <br>

# Link Wokwi:
https://wokwi.com/projects/381578713502156801
<br>

# Link vídeo - youtube:
https://youtu.be/OQHVNxoFPvY
<br>

# Circuito:
- ESP-32
- DHT22
- Ultrassônico
- Servo-motor
- LED Verde
- LED Amarelo
- LED Vermelho
- 3 Resistores (220 Ω)
- Buzzer
<br>

# Como funciona:
Utilizamos o DHT22 para medir a temperatura e umidade do estoque, e quando estão em níveis fora do ideal, o buzzer fica ligado.
<br> O buzzer liga quando a temperatura é maior que 25°C ou menor que 15°C, e/ou quando a umidade é maior que 70% ou menor que 40%.
<br> Além disso, o circuito trava a porta de abertura do estoque - exemplificamos isso com o servo-motor.
<br> <br>
E utilizamos o Sensor Ultrassônico para medir a distância entre o sensor e o remédio. Sabemos que cada estoque tem tamanhos diferentes, então utilizamos a medida de profundiade de 84cm, das pratelerias de refrigerador hospitalar da Indrel.
<br> Seguindo a lógica de que o sensor ficará na ponta da prateleira, e que quando um remédio for usado, o restante vai ficando mais profundo: quando maior o uso de um remédio, maior será a distância entre o restante e o sensor; e quando menor for o uso, menor será a disntância entre eles. E utilizamos os LEDS para sinalizar visualmente, de forma prática e rápida, qual é o status quo de cada remédio.<br>
Dessa forma, temos: 
<br> Quando a distância for menor que 35 cm, o LED Verde acende. 
<br> Quando a distância for entre 35 cm e 63 cm, o LED Amarelo acende.
<br> Quando a distância for maior que 63 cm, o LED Vermelho acende.
