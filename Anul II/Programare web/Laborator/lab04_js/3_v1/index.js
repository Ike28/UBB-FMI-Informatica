const boxes = document.querySelectorAll('.box');

let first;
let second;
let matchCounter = 0;

boxes.forEach(function (box) {
    box.style.order = Math.floor(Math.random() * 16).toString();
    box.addEventListener('click', function () {
        if (!first && !second) {
            first = box;
            box.classList.add('show');
        } else if (first && !second) {
            second = box;
            box.classList.add('show');
            if (first.innerHTML === second.innerHTML) {
                first.style.pointerEvents = 'none';
                second.style.pointerEvents = 'none';
                first = null;
                second = null;
                matchCounter++;
                if (matchCounter >= 8) setTimeout(() => window.alert("Congrats, you won! Refresh the page to keep playing!"), 1000);
            } else {
                first.classList.add('hide');
                second.classList.add('hide');
                setTimeout(() => {
                    first.classList.remove('show');
                    second.classList.remove('show');
                    first.classList.remove('hide');
                    second.classList.remove('hide');
                    first = null;
                    second = null;
                }, 2000);
            }
        }
    })
});