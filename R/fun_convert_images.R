
#' Convert image format.
#'
#' @param image The image to be converted. \code{getPerlin} writes images in
#' .bmp format which are not always what's required.
#' @param format The format argument to \code{magick::image_write}. Usually
#' "png".
#'
#' @return Nothing. Converts between image formats.
#' @export
#'
convert_images <- function(image, format = "png") {

    image_in <- magick::image_read(image)
    image_convert <- magick::image_convert(image_in, format = format)

    # write images
    magick::image_write(image_convert,
                        path = stringi::stri_sub(str = "test_image.bmp", 
                                       from = 1, to = -5))

}