window.onload = (event) => {
    main();
};

function main() {
    const canvas = document.getElementById('canvas');
    const context = canvas.getContext('2d');
    const speed = 200;
    
    // Setup hexashelfs
    const hexashelfs = [
        { pos: [20, 380], rgb: [255, 0, 0] },
        { pos: [52, 362], rgb: [255, 0, 0] },
        { pos: [52, 325], rgb: [255, 0, 0] },
        { pos: [84, 307], rgb: [255, 0, 0] },
        { pos: [116, 289], rgb: [255, 0, 0] },
        { pos: [148, 307], rgb: [255, 0, 0] },
        { pos: [180, 289], rgb: [255, 0, 0] },
        { pos: [180, 252], rgb: [255, 0, 0] },
        { pos: [148, 234], rgb: [255, 0, 0] },
        { pos: [148, 271], rgb: [255, 0, 0] },
        { pos: [116, 252], rgb: [255, 0, 0] },
        { pos: [84, 234], rgb: [255, 0, 0] },
        { pos: [52, 216], rgb: [255, 0, 0] },
        { pos: [52, 179], rgb: [255, 0, 0] },
        { pos: [84, 161], rgb: [255, 0, 0] },
        { pos: [84, 198], rgb: [255, 0, 0] },
        { pos: [116, 179], rgb: [255, 0, 0] },
        { pos: [148, 161], rgb: [255, 0, 0] },
        { pos: [180, 143], rgb: [255, 0, 0] },
        { pos: [180, 106], rgb: [255, 0, 0] },
        { pos: [148, 88], rgb: [255, 0, 0] },
        { pos: [148, 125], rgb: [255, 0, 0] },
        { pos: [116, 107], rgb: [255, 0, 0] }
    ];

    // Setup update interval and stop button
    let updateInterval = setInterval(update, speed);
    document.getElementById("stop").onclick = () => clearInterval(updateInterval);

    function drawHexagon(context, pos, rgb) {
        const numberOfSides = 6;
        const angle = (2 * Math.PI) / numberOfSides;
        const sideLength = 20;

        const [x, y] = pos;
        const [r, g, b] = rgb;

        context.beginPath();
        context.moveTo(x + sideLength * Math.cos(0), y + sideLength * Math.sin(0));

        for (let i = 1; i <= numberOfSides; i++) {
            context.lineTo(x + sideLength * Math.cos(i * angle), y + sideLength * Math.sin(i * angle));
        }

        context.closePath();
        context.fillStyle = `rgb(${r}, ${g}, ${b})`;
        context.fill();
        context.strokeStyle = 'black';
        context.stroke();
    }

    function interpolateColor(color1, color2, ratio) {
        const r = color1[0] + (color2[0] - color1[0]) * ratio;
        const g = color1[1] + (color2[1] - color1[1]) * ratio;
        const b = color1[2] + (color2[2] - color1[2]) * ratio;
        return [Math.round(r), Math.round(g), Math.round(b)];
    }
    
    function fadeColors(color, targetColor, steps) {
        const fadedColors = [];
        const color1 = color;
        const color2 = targetColor;
        const stepSize = 1 / (steps + 1);

        for (let j = 0; j <= steps; j++) {
            const ratio = j * stepSize;
            const interpolatedColor = interpolateColor(color1, color2, ratio);
            fadedColors.push(interpolatedColor);
        }

        return fadedColors;
    }

    const steps = 5;    
    const colors = [];

    //colors.push(...fadeColors([255, 0, 0], [0, 255, 0], steps));
    //colors.push(...fadeColors([0, 255, 0], [0, 0, 255], steps));
    //colors.push(...fadeColors([0, 0, 255], [255, 255, 0], steps));
    //colors.push(...fadeColors([255, 255, 0], [255, 0, 255], steps));
    //colors.push(...fadeColors([255, 0, 255], [255, 255, 255], steps));
    colors.push(...Array.from({ length: 9 }, () => [0, 0, 0]));
    colors.push(...fadeColors([0, 0, 0], [255, 255, 255], 2));
    colors.push(...fadeColors([255, 255, 255], [0, 0, 0], 2));
    colors.push(...Array.from({ length: 8 }, () => [0, 0, 0]));

    console.log(colors);

    let updates = 0;

    function update() {
        // Change colors
        for (let i = 0; i < hexashelfs.length; i++) {
            let color_i = i + updates;

            if (color_i >= colors.length) {
                color_i -= colors.length;
            }

            hexashelfs[i].rgb = colors[color_i];
        }

        // Redraw
        context.clearRect(0, 0, canvas.width, canvas.height);
        for (let i = 0; i < hexashelfs.length; i++) {
            drawHexagon(context, hexashelfs[i].pos, hexashelfs[i].rgb);
        }

        if (updates++ >= colors.length) {
            updates = 0;
        };
    }
}