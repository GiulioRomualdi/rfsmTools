/*
 * Copyright (C) 2017 iCub Facility
 * Authors: Nicolo' Genesio <nicogene@hotmail.it>
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include<rfsm.h>

/**
 * @brief The StateGraphEditor class provides the utilities for building/editing an rFSM
 * using rFSMGui
 */

class StateGraphEditor
{
private:
    rfsm::StateGraph* graph;
public:
    /**
     * @brief StateGraphEditor default constructor
     */
    StateGraphEditor();
    /**
     * @brief StateGraphEditor constructor
     * @param graph, rfsm::StateGraph to be built or edited
     */
    StateGraphEditor(rfsm::StateGraph &graph);
    /**
     * @brief ~StateGraphEditor
     */
    ~StateGraphEditor();
    /**
     * @brief setGraph, set the rfsm::StateGraph
     * @param graph
     */
    void setGraph(rfsm::StateGraph &graph);
    /**
     * @brief addState add a state specifying name and type(optional)
     * @param name of the state, it has to be unique in the entire state machine
     * @param type of the state, it can be simple, composit or connector
     */
    void addState(const std::string name,
                  const std::string type="simple");
    /**
     * @brief removeState remove the state with the given name
     * @param name of the state to be removed
     */
    void removeState(const std::string name);
    /**
     * @brief renameState change the name from oldName to newName
     * @param oldName, old name
     * @param newName, new name
     */
    void renameState(const std::string oldName, const std::string newName);
    /**
     * @brief addTransition, add a transition specifing source and target state name and events(optional)
     * @param source, name of the source state
     * @param target, name of the target state
     * @param events, list of events that triggers this transition
     */
    void addTransition(const std::string source,
                       const std::string target,
                       std::vector<std::string> events=std::vector<std::string>());
    /**
     * @brief addTransition, remove a transition specifing source and target state name and events(optional)
     * @param source, name of the source state
     * @param target, name of the target state
     * @param events, list of events that triggers this transition
     */
    void removeTransition(const std::string source,
                          const std::string target,
                          std::vector<std::string> events=std::vector<std::string>());
    /**
     * @brief updateTransitions, updates all the transitions linked to a state that changed name
     * @param oldName, old name of the state
     * @param newName, new name of the state
     */
    void updateTransitions(const std::string oldName, const std::string newName);

    /**
     * @brief addEvent, add a single event or more events separated by ',' for a transition defined
     * by source and target state name and events(optional)
     * @param source
     * @param target
     * @param event
     */
    void addEvent(const std::string source,
                  const std::string target,const std::string event);
    /**
     * @brief clearEvents, delete all events of the transition with those source and target state
     * @param source, name of the source state
     * @param target, name of the target state
     */
    void clearEvents(const std::string source,
                     const std::string target);
    /**
     * @brief getEvents get all the events related to a rfsm::StateGraph::Transition
     * @param source, name of the source state
     * @param target, name of the target state
     * @return the vector containing the events that trigger the rfsm::StateGraph::Transition tr
     */
    std::vector<std::string> getEvents(const std::string source,
                                       const std::string target);
    /**
     * @brief getPriority, get the priority related to a rfsm::StateGraph::Transition
     * @param source, name of the source state
     * @param target, name of the target state
     * @return the priority number
     */
    int getPriority(const std::string source,
                    const std::string target);
    /**
     * @brief setPriority, set the priority related to a rfsm::StateGraph::Transition
     * @param source, name of the source state
     * @param target, name of the target state
     * @param priority, priority to be assigned
     */
    void setPriority(const std::string source,
                     const std::string target,
                     int priority);

    /**
     * @brief getChilds, get the "first" childs of a state
     * @param state, name of the parent state
     * @param childs, vector of string containing the names of the childs
     * @return
     */
    void getChilds(const std::string state,
                   std::vector<std::string> &childs);

    /**
     * @brief getStateByName, it returns the rfsm::StateGraph::State given the name, assertion if not found
     * @param stateName, name of the state
     * @return
     */
    rfsm::StateGraph::State getStateByName(const std::string stateName);

    /**
     * @brief getParent, get the closest parent of a state
     * @param stateName, noame of the state
     * @return
     */
    std::string getParent(const std::string& stateName);

private:
    /**
     * @brief getTransition, return the first transition from/to a given state
     * @param stateName, name of the state (source or target)
     * @param from, boolean, if true this function return the first transition FROM stateName, TO otherwise
     * @param events
     * @return
     */
    rfsm::StateGraph::TransitionItr getTransition(const std::string stateName, bool from,
                          std::vector<std::string> events=std::vector<std::string>());
};
