

#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>

/*Colocar nome e senha do wifi*/
const char* ssid = "Inteli-COLLEGE";  // Inserir Nome aqui
const char* password = "QazWsx@123";  //Inserir senha aqui
// Definição dos pinos dos leds, do buzzer e de uma variavel auxiliar

#define SDA_PIN 9
#define SCL_PIN 10
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

WebServer server(80);             
 
void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Conectando ao ");
  Serial.println(ssid);

  //Conectar a rede wifi
  WiFi.begin(ssid, password);

  //Checar se o wifi está conectado
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado..!");
  // Print do wifi de acesso para a pagina html
  Serial.print("IP de acesso: ");  
  Serial.println(WiFi.localIP());

// Definição dos endpoints e das funções que eles chamam
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.on("/winone", winOne);
  server.on("/wintwo", winTwo);
  server.on("/empate", empate);
  server.begin();
  Serial.println("Servidor HTTP iniciado");

  // Definição dos pinos como outputs
  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.init();
  lcd.backlight();
}

void loop() {
  server.handleClient();
}

// Se o get ao endpoint for um sucesso manda o html
void handle_OnConnect() {
  server.send(200, "text/html", SendHTML()); 
}

// Se o get ao endpoint for mal sucedido da uma mensagem de não encontrado e um erro 404
void handle_NotFound(){
  server.send(404, "text/plain", "Não encontrado");
}

// Função de quando o player 1 ganha
void winOne(){
  Serial.println("Player 1 WIN");
  lcd.clear();
  lcd.println("Jogador 1 win");
  lcd.setCursor(0,1);
}

// Função de quando o player 2 ganha
void winTwo(){
  Serial.println("Player 2 WIN");
  lcd.clear();
  lcd.println("Jogador 2 win");
  lcd.setCursor(0,1);
}

// Função de quando o jogo empata
void empate(){
  Serial.println("Empate");
  lcd.clear();
  lcd.println("Empatou");
  lcd.setCursor(0,1);
}

// Função que escreve o html em uma string e retorna ele
String SendHTML(){
  String ptr = "<!DOCTYPE html> <html lang=\"en\">";
  ptr +="<head>\n";
  ptr +="<meta charset=\"UTF-8\">\n";
  ptr +="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  ptr +="<meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">\n";
  ptr +="<title>Tron game</title>\n";
  ptr +="<style>@import url('https://fonts.cdnfonts.com/css/games')\n";

  ptr +="body { \n";
  ptr +="background: #a0c404;\n";
  ptr +="text-align: center;\n";
  ptr +="font-family: 'Games', sans-serif;\n";
  ptr +="}\n";

  ptr +="#tron { \n";
  ptr +="border: 1px solid rgba(243, 3, 3, 0);\n";
  ptr +="outline: 1px solid #0000;\n";
  ptr +="outline-offset: 5px;\n";
  ptr +="}\n";

  ptr +="#playerO{ \n";
  ptr +="color:#000;\n";
  ptr +="}\n";

  ptr +="#playerT{ \n";
  ptr +="color: #000;\n";
  ptr +="}\n";

  ptr +=".sectionG{ \n";
  ptr +="display: flex;\n";
  ptr +="justify-content: space-around;\n";
  ptr +="}\n";

  ptr +="#pontsO{\n";
  ptr +="color: #2a8fa5;\n";
  ptr +="}\n";

  ptr +="#pontsT{\n";
  ptr +="color: #ed9e25;\n";
  ptr +="}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";

  ptr +="<body>\n";

  ptr +="<h1 style=\"color:#fff; margin:5px 0 5px 0;padding:0px;\">Jogo NOKIA da cobrinha</h1>\n";
  ptr +="<section class=\"sectionG\">\n";
  ptr +="<div>\n";
  ptr +="<h2 id=\"playerO\">Pontos jogador 1:</h2>\n";
  ptr +="<h2 id=\"pontsO\"></h2>\n";
  ptr +="</div>\n";
  ptr +="<canvas id=\"tron\" width=\"450\" height=\"450\"></canvas>\n";
  ptr +="<div>\n";
  ptr +="<h2 id=\"playerT\">Pontos jogador 2:</h2>\n";
  ptr +="<h2 id=\"pontsT\"></h2>\n";
  ptr +="</div>\n";
  ptr +="</section>\n";
  ptr +="<br>\n";
  ptr +="<p style=\"color:#fff;margin:0;\"><span style=\"color:#000;\">Jogador 1: WASD </span><span style=\"display: inline-block; margin: 0 15px;\"></span><span style=\"color:#000;\">Jogador 2:↑↓←→</span></p>\n";
  ptr +="<script> const canvas = document.getElementById(\"tron\");\n";
  ptr +="const context = canvas.getContext(\"2d\");\n";
  ptr +="const unit = 15;\n";
  ptr +="const counterpo = document.getElementById(\"pontsO\");\n";
  ptr +="const counterpt = document.getElementById(\"pontsT\");\n";
  ptr +="var po = 0;\n";
  ptr +="var pt = 0;\n";

  ptr +="class Player {\n";
  ptr +="constructor(x, y, color) {\n";
  ptr +="this.color = color || \"#fff\";\n";
  ptr +="this.dead = false;\n";
  ptr +="this.direction = \"\";\n";
  ptr +="this.key = \"\";\n";
  ptr +="this.x = x;\n";
  ptr +="this.startX = x;\n";
  ptr +="this.startY = y;\n";

  ptr +="this.constructor.counter = (this.constructor.counter || 0) + 1;\n";
  ptr +="this._id = this.constructor.counter;\n";

  ptr +="Player.allInstances.push(this);\n";
  ptr +="}\n";
  ptr +="}\n";

  ptr +="Player.allInstances = [];\n";


  ptr +="let p1 = new Player(unit * 3, unit * 15, \"#0000\");\n";
  ptr +="let p2 = new Player(unit * 26, unit * 15, \"#0000\");\n";

  ptr +="function setKey(key, player, up, right, down, left) {\n";
  ptr +="switch (key) {\n";
  ptr +="case up:\n";
  ptr +="if (player.direction !== \"DOWN\") {\n";
  ptr +="player.key = \"UP\";\n";
  ptr +="}\n";
  ptr +="break;\n";
  ptr +="case right:\n";
  ptr +="if (player.direction !== \"LEFT\") {\n";
  ptr +="player.key = \"RIGHT\";\n";
  ptr +="}\n";
  ptr +="break;\n";
  ptr +="case down:\n";
  ptr +="if (player.direction !== \"UP\") {\n";
  ptr +="player.key = \"DOWN\";\n";
  ptr +="}\n";
  ptr +="break;\n";
  ptr +="case left:\n";
  ptr +="if (player.direction !== \"RIGHT\") {\n";
  ptr +="player.key = \"LEFT\";\n";
  ptr +="}\n";
  ptr +="break;\n";
  ptr +="default:\n";
  ptr +="break;\n";
  ptr +="}\n";
  ptr +="}\n";

  ptr +="function handleKeyPress(event) {\n";
  ptr +="let key = event.keyCode;\n";

  ptr +="if (key === 37 || key === 38 || key === 39 || key === 40) {\n";
  ptr +="event.preventDefault();\n";
  ptr +="}\n";

  ptr +="setKey(key, p1,87, 68, 83, 65 ); // Setas teclado - Jogador 1\n";
  ptr +="setKey(key, p2, 38, 39, 40, 37); // WASD - Jogador 2 \n";
  ptr +="}\n";

  ptr +="document.addEventListener(\"keydown\", handleKeyPress);\n";

  ptr +="function getPlayableCells(canvas, unit) {\n";
  ptr +="let playableCells = new Set();\n";
  ptr +="for (let i = 0; i < canvas.width / unit; i++) {\n";
  ptr +="for (let j = 0; j < canvas.height / unit; j++) {\n";
  ptr +="playableCells.add(`${i * unit}x${j * unit}y`);\n";
  ptr +="}\n";
  ptr +="}\n";
  ptr +="return playableCells;\n";
  ptr +="}\n";

  ptr +="let playableCells = getPlayableCells(canvas, unit);\n";

  ptr +="function drawBackground() {\n";
  ptr +="context.strokeStyle = \"#a0c404\";\n";
  ptr +="for (let i = 0; i <= canvas.width / unit + 2; i += 2) {\n";
  ptr +="for (let j = 0; j <= canvas.height / unit + 2; j += 2) {\n";
  ptr +="context.strokeRect(0, 0, unit * i, unit * j);\n";
  ptr +="}\n";
  ptr +="}\n";

  ptr +="context.strokeStyle = \"#FFFF\";\n";
  ptr +="context.lineWidth = 2;\n";
  ptr +="for (let i = 1; i <= (canvas.width + unit) / unit; i += 2) {\n";
  ptr +="for (let j = 1; j <= (canvas.height + unit) / unit; j += 2) {\n";
  ptr +="context.strokeRect(0, 0, unit * i, unit * j);\n";
  ptr +="}\n";
  ptr +="}\n";
  ptr +="context.lineWidth = 1;\n";
  ptr +="}\n";

  ptr +="drawBackground();\n";

  ptr +="function drawStartingPositions(players) {\n";
  ptr +="players.forEach((p) => {\n";
  ptr +="context.fillStyle = p.color;\n";
  ptr +="context.fillRect(p.x, p.y, unit, unit);\n";
  ptr +="context.strokeStyle = \"black\";\n";
  ptr +="context.strokeRect(p.x, p.y, unit, unit);\n";
  ptr +="});\n";
  ptr +="}\n";

  ptr +="drawStartingPositions(Player.allInstances);\n";

  ptr +="let outcome,\n";
  ptr +="winnerColor,\n";
  ptr +="playerCount = Player.allInstances.length;\n";

  ptr +="function draw() {\n";
  ptr +="if (Player.allInstances.filter((p) => !p.key).length === 0) {\n";
  ptr +="console.log(\"cgem rolando\");\n";
  ptr +="if (playerCount === 1) {\n";
  ptr +="const alivePlayers = Player.allInstances.filter((p) => p.dead === false);\n";
  ptr +="outcome = `Jogador ${alivePlayers[0]._id} venceu!!!`;\n";
  ptr +="console.log(\"player vencedor é\" + alivePlayers[0]._id);\n";
  ptr +="if(alivePlayers[0]._id === 1){\n";
   ptr += "var wpt = new XMLHttpRequest(); \n";
  ptr += "wpt.open(\"GET\", \"/winone\", true);\n";
  ptr += "wpt.send();\n";
  ptr +="po++\n";
  ptr +="}\n";
  ptr +="if(alivePlayers[0]._id === 2){\n";
  ptr += "var wpt = new XMLHttpRequest(); \n";
  ptr += "wpt.open(\"GET\", \"/wintwo\", true);\n";
  ptr += "wpt.send();\n";
  ptr +="pt++\n";
  ptr +="}\n";
  ptr +="winnerColor = alivePlayers[0].color;\n";
  ptr +="} else if (playerCount === 0) {\n";
  ptr +="outcome = \"Empate!\";\n";
   ptr += "var wpt = new XMLHttpRequest(); \n";
  ptr += "wpt.open(\"GET\", \"/empate\", true);\n";
  ptr += "wpt.send();\n";
  ptr +="}\n";

  ptr +="if (outcome) {\n";
  ptr +="createResultsScreen(winnerColor);\n";
  ptr +="clearInterval(game);\n";
  ptr +="}\n";

  ptr +="Player.allInstances.forEach((p) => {\n";
  ptr +="if (p.key) {\n";
  ptr +="p.direction = p.key;\n";

  ptr +="context.fillStyle = p.color;\n";
  ptr +="context.fillRect(p.x, p.y, unit, unit);\n";
  ptr +="context.strokeStyle = \"black\";\n";
  ptr +="context.strokeRect(p.x, p.y, unit, unit);\n";

  ptr +="if (!playableCells.has(`${p.x}x${p.y}y`) && p.dead === false) {\n";
  ptr +="p.dead = true;\n";
  ptr +="p.direction = \"\";\n";
  ptr +="playerCount -= 1;\n";
  ptr +="}\n";

  ptr +="playableCells.delete(`${p.x}x${p.y}y`);\n";

  ptr +="if (!p.dead) {\n";
  ptr +="if (p.direction === \"LEFT\") p.x -= unit;\n";
  ptr +="if (p.direction === \"UP\") p.y -= unit;\n";
  ptr +="if (p.direction === \"RIGHT\") p.x += unit;\n";
  ptr +="if (p.direction === \"DOWN\") p.y += unit;\n";
  ptr +="}\n";
  ptr +="}\n";
  ptr +="});\n";
  ptr +="}\n";
  ptr +="}\n";

  ptr +="let game = setInterval(draw, 100);\n";

  ptr +="function createResultsScreen(color) {\n";
  ptr +="const resultNode = document.createElement(\"div\");\n";
  ptr +="resultNode.id = \"result\";\n";
  ptr +="resultNode.style.color = color || \"#fff\";\n";
  ptr +="resultNode.style.position = \"fixed\";\n";
  ptr +="resultNode.style.top = 0;\n";
  ptr +="resultNode.style.display = \"grid\";\n";
  ptr +="resultNode.style.gridTemplateColumns = \"1fr\";\n";
  ptr +="resultNode.style.width = \"100%\";\n";
  ptr +="resultNode.style.height = \"100vh\";\n";
  ptr +="resultNode.style.justifyContent = \"center\";\n";
  ptr +="resultNode.style.alignItems = \"center\";\n";
  ptr +="resultNode.style.background = \"#00000088\";\n";

  ptr +="const resultText = document.createElement(\"h1\");\n";
  ptr +="resultText.innerText = outcome;\n";
  ptr +="resultText.style.fontFamily = \"Games, sans-serif\";\n";
  ptr +="resultText.style.textTransform = \"uppercase\";\n";

  ptr +="const replayButton = document.createElement(\"button\");\n";
  ptr +="replayButton.innerText = \"Jogar novamente\";\n";
  ptr +="replayButton.style.fontFamily = \"Games, sans-serif\";\n";
  ptr +="replayButton.style.textTransform = \"uppercase\";\n";
  ptr +="replayButton.style.padding = \"10px 30px\";\n";
  ptr +="replayButton.style.fontSize = \"1.2rem\";\n";
  ptr +="replayButton.style.margin = \"0 auto\";\n";
  ptr +="replayButton.style.cursor = \"pointer\";\n";
  ptr +="replayButton.onclick = resetGame;\n";

  ptr +="resultNode.appendChild(resultText);\n";
  ptr +="resultNode.appendChild(replayButton);\n";
  ptr +="document.querySelector(\"body\").appendChild(resultNode);\n";

  ptr +="document.addEventListener(\"keydown\", (e) => {\n";
  ptr +="let key = event.keyCode;\n";
  ptr +="if (key == 32) resetGame();\n";
  ptr +="});\n";
  ptr +="}\n";

  ptr +="function resetGame() {\n";
  ptr +="const result = document.getElementById(\"result\");\n";
  ptr +="if (result) result.remove();\n";


  ptr +="context.clearRect(0, 0, canvas.width, canvas.height);\n";
  ptr +="drawBackground();\n";


  ptr +="playableCells = getPlayableCells(canvas, unit);\n";

  ptr +="Player.allInstances.forEach((p) => {\n";
  ptr +="p.x = p.startX;\n";
  ptr +="p.y = p.startY;\n";
  ptr +="p.dead = false;\n";
  ptr +="p.direction = \"\";\n";
  ptr +="p.key = \"\";\n";
  ptr +="});\n";
  ptr +="playerCount = Player.allInstances.length;\n";
  ptr +="drawStartingPositions(Player.allInstances);\n";

  ptr +="outcome = \"\";\n";
  ptr +="winnerColor = \"\";\n";

  ptr +="clearInterval(game);\n";
  ptr +="game = setInterval(draw, 100);\n";
  ptr +="console.log(\"Vitórias player 1\" + po);\n";
  ptr +="console.log(\"Vitórias player 2\" + pt);\n";
  ptr +="counterpo.innerHTML = po;\n";
  ptr +="counterpt.innerHTML = pt;\n";
  ptr +="} \n";
  ptr +="</script>\n";

  ptr +="</body>\n";

  ptr +="</html>\n";

return ptr;
}