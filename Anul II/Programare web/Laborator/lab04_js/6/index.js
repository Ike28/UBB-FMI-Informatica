const puzzleContainer = document.getElementById('puzzle');

let puzzle = [];
let size = 3; // 3 x 3 grid

playGame();

function playGame() {
    generatePuzzle();
    randomizePuzzle();
    renderPuzzle();
    handleInput();
}

function getRow(pos) {
    return Math.ceil(pos / size);
}

function getColumn(pos) {
    let column = pos % size;
    if (column === 0) {
        return size;
    }
    return column;
}

function generatePuzzle() {
    for (let i = 1; i <= size * size; i++) {
        puzzle.push({
            value: i,
            position: i,
            x: (getColumn(i) - 1) * Math.ceil(600 / size),
            y: (getRow(i) - 1) * Math.ceil(600 / size),
            disabled: false,
        });
    }
}

function renderPuzzle() {
    puzzleContainer.innerHTML = '';
    for (let pz of puzzle) {
        if (pz.disabled === true) continue;
        const puzzleItem = document.createElement('div');
        puzzleItem.setAttribute('id', 'puzzleItem');
        puzzleItem.setAttribute('style', `left: ${pz.x}px; top:${pz.y}px;`);
        puzzleItem.innerText = pz.value;
        puzzleContainer.appendChild(puzzleItem);
    }
}

function generateRandoms(size) {
    const numbers = [];
    for (let i = 1; i <= size * size; i++) {
        numbers.push(i);
    }
    return numbers.sort(() => Math.random() - 0.5);
}

function randomizePuzzle() {
    const randoms = generateRandoms(size);
    let i = 0;
    for (let pz of puzzle) {
        pz.value = randoms[i];
        i++;
    }
    const hiddenPiece = puzzle.find((item) => item.value === size * size);
    hiddenPiece.disabled = true;
}

function handleKeydown(o) {
    console.log(o.key);
    switch (o.key) {
        case "ArrowLeft":
            moveLeft();
            break;
        case "ArrowRight":
            moveRight();
            break;
        case "ArrowUp":
            moveUp();
            break;
        case "ArrowDown":
            moveDown();
            break;
    }
    renderPuzzle();
}

function swapPieces(firstPiece, secondPiece, isX = false) {
    let temp = firstPiece.position;
    firstPiece.position = secondPiece.position;
    secondPiece.position = temp;

    if (isX) {
        temp = firstPiece.x;
        firstPiece.x = secondPiece.x;
        secondPiece.x = temp;
    } else {
        temp = firstPiece.y;
        firstPiece.y = secondPiece.y;
        secondPiece.y = temp;
    }
}

function moveLeft() {
    const emptyPiece = getEmptyPiece();
    const rightPiece = getRightPiece();
    if (rightPiece) {
        swapPieces(emptyPiece, rightPiece, true);
    }
}

function moveRight() {
    const emptyPiece = getEmptyPiece();
    const leftPiece = getLeftPiece();
    if (leftPiece) {
        swapPieces(emptyPiece, leftPiece, true);
    }
}

function moveUp() {
    const emptyPiece = getEmptyPiece();
    const downPiece = getDownPiece();
    if (downPiece) {
        swapPieces(emptyPiece, downPiece, false);
    }
}

function moveDown() {
    const emptyPiece = getEmptyPiece();
    const upperPiece = getUpPiece();
    if (upperPiece) {
        swapPieces(emptyPiece, upperPiece, false);
    }
}

function getEmptyPiece() {
    return puzzle.find((item) => item.disabled);
}

function getPuzzleByPosition(pos) {
    return puzzle.find((item) => item.position === pos);
}

function getRightPiece() {
    const emptyPuzzle = getEmptyPiece();
    //checking if the hidden piece is on the right edge
    if (getColumn(emptyPuzzle.position) === size) {
        return null;
    }
    return getPuzzleByPosition(emptyPuzzle.position + 1);
}

function getLeftPiece() {
    const emptyPuzzle = getEmptyPiece();
    //checking if the hidden piece is on the left edge
    if (getColumn(emptyPuzzle.position) === 1) {
        return null;
    }
    return getPuzzleByPosition(emptyPuzzle.position - 1);
}

function getUpPiece() {
    const emptyPuzzle = getEmptyPiece();
    //checking if the hidden piece is on the upper edge
    if (getRow(emptyPuzzle.position) === 1) {
        return null;
    }
    return getPuzzleByPosition(emptyPuzzle.position - size);
}

function getDownPiece() {
    const emptyPuzzle = getEmptyPiece();
    //checking if the hidden piece is on the lower edge
    if (getRow(emptyPuzzle.position) === size) {
        return null;
    }
    return getPuzzleByPosition(emptyPuzzle.position + size);
}

function handleInput() {
    document.addEventListener('keydown', handleKeydown);
}