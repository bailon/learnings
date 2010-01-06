/******************************************************************************
 * Universidade Federal de Pelotas
 * Ciência da Computação - Programação Orientada a Objetos
 * 
 * Grupo: Bruno Rodrigues, Eduardo Saffer, Marco Beckmann
 * Data: 3 de Dezembro de 2008
 *
 * Este programa tem o objetivo deresolver uma equação da fractal de Mandelbrot
 * utilizando Threads.
 ******************************************************************************/
 
import java.awt.*;

/**
 * Esta classe realiza o calculo da fractal de Mandelbrot utilizando threads
 * calculando cada ponto da imagem e setando uma cor para esse ponto.
 **/
public class Pinta extends Thread {
	double xc, yc, size;
	int N, max, ilim, jlim, iini, jini;
	Picture pic;
	
	
	// Seta as variáveis da classe
	public Pinta(double xc, double yc, double size, int N, int max, Picture pic, int ilim, int jlim, int iini, int jini){
		this.xc = xc;
		this.yc = yc;
		this.N = N;
		this.max = max;
		this.pic = pic;
		this.ilim = ilim;
		this.jlim = jlim;
		this.size = size;
		this.iini = iini;
		this.jini = jini;
	}
	
	
	/**
	 * Verifica se o valor é um número de Mandelbrot
	 **/
	public int mand(Complex z0, int max) {
		Complex z = z0;

		for (int t = 0; t < max; t++) {
			if (z.abs() > 2.0)
				return t;
			z = z.times(z).plus(z0);
		}
		return max;
	}

	/**
	 * Realiza o calculo de Mandelbrot
	 **/
	public void run() {
		for (int i = 0; i < ilim; i++) {
			for (int j = 0; j < jlim; j++) {
				double x0 = xc - size/2 + size*i/N;
				double y0 = yc - size/2 + size*j/N;
				Complex z0 = new Complex(x0, y0);
				int gray = max - mand(z0, max);
				Color color = new Color(gray, gray, gray);
				pic.set(i, N-1-j, color);
			}
		}
	}
}
