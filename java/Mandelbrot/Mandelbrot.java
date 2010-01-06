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
import java.math.*;


/**
 * Esta classe define uma fractal de Mandelbrot. Ela reealiza as chamadas as threads
 * e monta a imagem finalizada. Que é exibida pela classe Picture.
 **/      
public class Mandelbrot
{
	public static void main(String[] args)  {
		double xc, yc, size;
		int th;
		int N   = 600;
		int max;
		int k, i, j;
		Color c;

		// Tenta pegar os parâmetros da linha de comando, senão,
		// coloca um valor padrão.
		try { th = Integer.parseInt(args[0]); }
		catch (ArrayIndexOutOfBoundsException e) { th = 6; }
		
		try { max = Integer.parseInt(args[1]); }
		catch (ArrayIndexOutOfBoundsException e) { max = 255; }
		 
		try { xc = Double.parseDouble(args[2]); }
		catch (ArrayIndexOutOfBoundsException e) { xc = -.5; }
		
		try { yc = Double.parseDouble(args[3]); } 
		catch (ArrayIndexOutOfBoundsException e) { yc = 0; }
		
		try { size = Double.parseDouble(args[4]); }
		catch (ArrayIndexOutOfBoundsException e) { size = 2; }
		

		Picture pic = new Picture(N, N);	// Nova superfície de imagem
		Pinta cinza[] = new Pinta[th];		// Threads para pintura
		
		
		// Cria uma nova thread, dividindo a imagem em partes
		for (k=0; k < th; k++) {
			cinza[k] = new Pinta(xc, yc, size, N, max, pic, (N/th)*(k+1), (N/th)*(k+1), (N/th)*(k), (N/th)*(k));
			cinza[k].start();
		}
		
		
		// Seta o join, para esperar o resultado de todos as threads abertas
		for (k=0; k < th; k++) {
			try {
				cinza[k].join();
			}
			catch (InterruptedException e) { }
		}
		
		// Imprime  a imagem completa		
		pic.show();
	}
}
