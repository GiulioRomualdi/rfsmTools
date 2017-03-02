--
-- Copyright (C) 2015 iCub Facility
-- Authors: Nicolò Genesio
-- CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
--


return rfsm.state {
    Configure = rfsm.csta {
--        Software = rfsm.sista{ },
--        Hardware = rfsm.sista{ },
--        rfsm.transition { src='initial', tgt='Software'},
--        rfsm.transition { src='Software', tgt='Hardware'},
    },

    UpdateModule = rfsm.sista{
        entry = function()
            print("entry() of UpdateModule (hello from Lua)")
        end,

        doo  = function()
            print("entry() of UpdateModule (hello from Lua)")
        end,

        exit = function()
            print("entry() of UpdateModule (hello from Lua)")
        end,
    },

    Close = rfsm.sista{
        entry = function()
            print("entry() of Close (hello from Lua)")
        end,
    },

    InterruptModule = rfsm.sista{
        entry = function()
            print("entry() of InterruptModule (hello from Lua)")
        end,
    },


    rfsm.transition { src='initial', tgt='Configure' },
    rfsm.transition { src='Configure', tgt='UpdateModule', events={ 'e_true' } },
    rfsm.transition { src='Configure', tgt='Close', events={ 'e_false' } },
    rfsm.transition { src='Configure', tgt='InterruptModule', events={ 'e_stopModule','e_interrupt' } },
    rfsm.transition { src='UpdateModule', tgt='UpdateModule', events={ 'e_true' } },
    rfsm.transition { src='UpdateModule', tgt='Close', events={ 'e_false' } },
    rfsm.transition { src='UpdateModule', tgt='InterruptModule', events={ 'e_stopModule','e_interrupt' } },
    rfsm.transition { src='InterruptModule', tgt='Close' },
}

