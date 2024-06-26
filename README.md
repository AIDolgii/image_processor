# Графические фильтры (image_processor)
## Поддерживаемый формат изображений
- BMP (24 bit)

## Формат аргументов командной строки
Описание формата аргументов командной строки:

`{имя программы} {путь к входному файлу} {путь к выходному файлу}
[-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...]
[-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ...`


## Реализованные фильтры и как их трогать
Пример использования:
````./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5```` 

- ``-crop width height`` (crop) — обрезает изображение до указанных размеров (типа unsigned int) (по левому верхнему углу)
- ``-gs`` (grayscale) — преобразует изображение в оттенки серого
- ``-neg`` (negative) — инвертирует цвета изображения
- ``-sharp`` (sharpening) — увеличивает резкость изображения
- ``-edge threshold`` (edge detection) — выделяет границы объектов на изображении с порогом threshold (типа float)
- ``-blur sigma`` (blur) — размывает по Гауссу изображение с параметром sigma (типа float)
- ``-cryst step_size`` (crystallize) — кристаллизует изображение с шагом step_size (типа unsigned int)