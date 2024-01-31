package ca.cmpt213.as3.logic;
import ca.cmpt213.as3.ui.gameGrid;

/**
 * @author Jai Malhi
 * Interface used for the spell options, implemented by userInterface
 */
public interface spellOptions {
    //Spell option, jump player to another grid location
    void teleportPlayerTo(gameGrid gg);
    //Spell option, randomly reveal the location of one of the Tokimons
    void revealToki(gameGrid gg, gridLogic gl);
    //Spell option, randomly kill off one of the Fokimons
    void killFoki(gameGrid gg, gridLogic gl);
}
