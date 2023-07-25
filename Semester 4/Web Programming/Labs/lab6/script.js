let size = 4;
let numberOfTiles = size ** 2;
let highlighted = numberOfTiles;
let shuffled = false;

let buttonContainer = $('#tiles');

newGame();

function newGame() {
    loadTiles();
    shuffle();
}

// create buttons
function loadTiles() {
    
    for (let b = 1; b <= numberOfTiles; b++) {
        var newTile = $(`<button id='btn${b}' index='${b}' class='btn'>${b}</button>`);
        newTile.on('click', function() {
            swap(parseInt($(this).attr('index')));
        });

        buttonContainer.append(newTile);
    }
   
    $(`#btn${highlighted}`).addClass("selected");  //selected tile

}

function shuffle() {
    let minShuffles = 2;
    let totalShuffles = 200;
  
    $.each(Array(totalShuffles), function(index) { 
      setTimeout(function() {
        let x = Math.floor(Math.random() * 4);
        let direction = 0;
        if (x == 0) { //the cell to the right
          direction = highlighted + 1;
        } else if (x == 1) { //left
          direction = highlighted - 1;
        } else if (x == 2) { //below
          direction = highlighted + size;
        } else if (x == 3) { //up
          direction = highlighted - size;
        }
        swap(direction);
        if (index == totalShuffles - minShuffles) { 
          shuffled = true;
        }
      }, (index + minShuffles) * 10); //delay 
    });
  }

// Swap tiles 
function swap(clicked) {
    if (clicked < 1 || clicked > (numberOfTiles)) {
        return;
    }

    // Check if we are trying to swap left (is to the right of the highl)
    if (clicked == highlighted + 1) {
        if (clicked % size != 1) { 
            setSelected(clicked);
        }
        // right
    } else if (clicked == highlighted - 1) {
        if (clicked % size != 0) { 
            setSelected(clicked);
        }
        // up
    } else if (clicked == highlighted + size) { //click is down
        setSelected(clicked);
        // down 
    } else if (clicked == highlighted - size) {
        setSelected(clicked);
    }

    if (shuffled) {
        if (checkHasWon()) {
            alert("Winner!")
        }
    }
}

function checkHasWon() {
    let allTilesMatch = true;
    $('.btn').each(function(index) { 
        let currentTileIndex = $(this).attr('index');
        let currentTileValue = $(this).text();
        if (parseInt(currentTileIndex) != parseInt(currentTileValue)) {
            allTilesMatch = false;
            return false; 
        }
    });
    return allTilesMatch; 
}


function setSelected(index) {
    currentTile = $(`#btn${highlighted}`);
    currentTileText = currentTile.text();
    currentTile.removeClass('selected');
    newTile = $(`#btn${index}`);
    currentTile.text(newTile.text());
    newTile.text(currentTileText);
    newTile.addClass('selected');
    highlighted = index;
}
