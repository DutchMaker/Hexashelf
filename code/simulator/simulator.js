window.onload = (event) => {
    main();
};

function main() {
    const canvas = document.getElementById('canvas');
    const context = canvas.getContext('2d');
    const speeds = [ 200, 50, 100, 200 ];
    const animation = 2;
    
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
    let updateInterval = setInterval(update, speeds[animation - 1]);
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

        for (let j = 0; j <= steps; j++) {
            fadedColors.push(fadeColor(color, targetColor, steps, j));
        }

        return fadedColors;
    }

    function fadeColor(color, targetColor, rangeSize, step) {
        const fadedColors = [];
        const color1 = color;
        const color2 = targetColor;
        const stepSize = 1 / (rangeSize + 1);

        const ratio = step * stepSize;
        return interpolateColor(color1, color2, ratio);
    }

    function hslToRgb(h, s, l) {
        let r, g, b;
    
        if (s === 0) {
            r = g = b = l;
        } else {
            const hue2rgb = (p, q, t) => {
                if (t < 0) t += 1;
                if (t > 1) t -= 1;
                if (t < 1 / 6) return p + (q - p) * 6 * t;
                if (t < 1 / 2) return q;
                if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
                return p;
            };
    
            const q = l < 0.5 ? l * (1 + s) : l + s - l * s;
            const p = 2 * l - q;
    
            r = hue2rgb(p, q, h + 1 / 3);
            g = hue2rgb(p, q, h);
            b = hue2rgb(p, q, h - 1 / 3);
        }
    
        return [Math.round(r * 255), Math.round(g * 255), Math.round(b * 255)];
    }
    
    // Setup colors for animation 1.
    const colors_1 = [];
    colors_1.push(...Array.from({ length: 17 }, () => [0, 0, 0]));
    colors_1.push(...fadeColors([0, 0, 0], [255, 255, 255], 2));
    colors_1.push(...fadeColors([255, 255, 255], [0, 0, 0], 2));

    // Setup colors for animation 2.
    const colors_2 = [];
    //colors_2.push(...Array.from({ length: 17 }, () => [0, 0, 0]));
    colors_2.push(...fadeColors([0, 255, 0], [255, 0, 0], 20));
    colors_2.push(...fadeColors([255, 0, 0], [255, 255, 0], 40));
    colors_2.push(...fadeColors([255, 255, 0], [0, 255, 255], 40));
    colors_2.push(...fadeColors([0, 255, 255], [255, 0, 255], 40));
    colors_2.push(...fadeColors([255, 0, 255], [255, 255, 255], 40));
    colors_2.push(...fadeColors([255, 255, 255], [0, 255, 0], 20));

    let counter = 0;

    function update() {
        handle_animation();
        redraw();
    }

    function handle_animation() {
        switch (animation) {
            case 1:
                handle_animation_1();
                break;
            case 2:
                handle_animation_2();
                break;
            case 3:
                handle_animation_3();
                break;
            case 4:
                handle_animation_4();
                break;
        }
    }

    function redraw() {
        context.clearRect(0, 0, canvas.width, canvas.height);
        for (let i = 0; i < hexashelfs.length; i++) {
            drawHexagon(context, hexashelfs[i].pos, hexashelfs[i].rgb);
        }
    }

    function handle_animation_1() {
        for (let i = 0; i < hexashelfs.length; i++) {
            let color_i = i + counter;

            if (color_i >= colors_1.length) {
                color_i -= colors_1.length;
            }

            hexashelfs[i].rgb = colors_1[color_i];
        }

        if (counter++ >= colors_1.length) {
            counter = 0;
        };
    }

    function handle_animation_2() {
        for (let i = 0; i < hexashelfs.length; i++) {
            let color_i = i + counter;

            if (color_i >= colors_2.length) {
                color_i -= colors_2.length;
            }

            hexashelfs[i].rgb = colors_2[color_i];
        }

        if (counter++ >= colors_2.length) {
            counter = 0;
        };
    }

    function handle_animation_3() {
        const hue = counter / 360;
        const rgb = hslToRgb(hue, 1, 0.5);

        for (let i = 0; i < hexashelfs.length; i++) {
            
            hexashelfs[i].rgb = rgb;
        }

        if (counter++ >= 360) {
            counter = 0;
        }
    }

    function handle_animation_4() {
        for (let i = 0; i < hexashelfs.length; i++) {
            let color_i = i + counter;

            if (color_i > 22) {
                color_i -= 22;
            }

            let c = (i < 12) 
                ? fadeColor([0, 0, 0], [255, 255, 255], 10, color_i)
                : fadeColor([255, 255, 255], [0, 0, 0], 11, color_i - 10);

            hexashelfs[i].rgb = c;
        }

        if (counter++ > 22) {
            counter = 0;
        };
    }
}