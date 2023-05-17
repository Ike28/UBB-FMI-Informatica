document.addEventListener("DOMContentLoaded", function () {
    const table = document.getElementById('fruits');
    const headers = table.querySelectorAll('th');
    const tableBody = table.querySelector('tbody');
    const rows = tableBody.querySelectorAll('tr');

    const directions = Array.from(headers).map(function (header) {
        return '';
    });

    function transform(index, content) {
        const type = headers[index].getAttribute('data-type');
        switch (type) {
            case "number":
                return parseInt(content);
            case "string":
                return content;
            default:
                return content;
        }
    }

    function sortColumn(index) {
        const newRows = Array.from(rows); //shallow-copy of rows

        const direction = directions[index] || 'asc';
        let multiplier;
        if (direction === 'asc') {
            multiplier = 1;
        } else multiplier = -1;

        newRows.sort(function (rowA, rowB) {
            const cellA = rowA.querySelectorAll('td')[index].innerHTML;
            const cellB = rowB.querySelectorAll('td')[index].innerHTML;

            const a = transform(index, cellA);
            const b = transform(index, cellB);

            switch (true) {
                case a > b:
                    return multiplier;
                case a < b:
                    return -1 * multiplier;
                case a === b:
                    return 0;
            }
        });

        [].forEach.call(rows, function (row) {
            tableBody.removeChild(row);
        });

        //reversing the direction
        if (direction === 'asc') {
            directions[index] = 'desc';
        } else {
            directions[index] = 'asc';
        }

        newRows.forEach(function (newRow) {
            tableBody.appendChild(newRow);
        })
    }

    [].forEach.call(headers, function (header, index) {
        header.addEventListener('click', function () {
            sortColumn(index);
        });
    });
});